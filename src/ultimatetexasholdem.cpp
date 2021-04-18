#include "ultimatetexasholdem.h"
#include "ui_ultimatetexasholdem.h"
#include <algorithm>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <string>
#include <QTime>
#include <stdexcept>
#include <type_traits>

#include "roundresultservice.h"
#include "include/handranker.h"
#include "include/endofrounddialogwindow.h"
#include "warningdialog.h"



UltimateTexasHoldem::UltimateTexasHoldem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UltimateTexasHoldem),
    backcard((":/cards/resources/backcard.png"))
{
    filterMouseEvents = new FilterMouseEvents(this);
    backcard = backcard.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio);
    ui->setupUi(this);
    setUiConnections();

    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);// no resizing

    hideAllCards();
    setUiToBetting();

    ui->money->setText(QString::number(player.money));

}

UltimateTexasHoldem::~UltimateTexasHoldem()
{
    delete ui;
}

/**
 * @brief UltimateTexasHoldem::setUiConnections Function sets any ui connects required for this object
 */
void UltimateTexasHoldem::setUiConnections() {
    connect(ui->anteSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotEqualAnteBlindBoxes(int)));
    connect(ui->blindSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotEqualAnteBlindBoxes(int)));
}

/**
 * @brief createEndOfRoundDialog Function creates a dialog representing the end of the round
 *   The dialog is blocking dialog.
 * @param roundResult The round result object to supply to the dialog
 */
void createEndOfRoundDialog(const RoundResult& roundResult) {
    EndOfRoundDialogWindow dialog(roundResult);
    dialog.setModal(true); //dont allow context switching
    dialog.exec();
}

/**
 * @brief createWarningMessage Function creates a warning dialog
 * @param message The warning to display on the dialog
 */
void createWarningMessage(const QString& message) {
    WarningDialog dialog(message);
    dialog.setModal(true); //dont allow context switching
    dialog.exec();
}

/**
 * @brief UltimateTexasHoldem::setUiToBetting
 * Makes the UI go to the betting stage where all cards are down
 * And the user can place bets
 * This is a hard reset of the UI
 */
void UltimateTexasHoldem::setUiToBetting() {
    // dealing buttons
    ui->dealButton->setEnabled(true);
    ui->bet1XButton->setEnabled(false);
    ui->bet2XButton->setEnabled(false);
    ui->bet3XButton->setEnabled(false);
    ui->bet4XButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->foldButton->setEnabled(false);

    // betting buttons
    ui->anteSpinBox->setEnabled(true);
    ui->blindSpinBox->setEnabled(true);
    ui->tripSpinBox->setEnabled(true);

    numOfChecks = 0;

}

/**
 * @brief UltimateTexasHoldem::setUiToInitalDeal
 * Makes the UI go to the first stage of dealing, where all cards are down
 * But the user can now check and perform checking or betting xn amonts
 * This is a hard reset of the UI
 */
void UltimateTexasHoldem::setUiToInitalDeal() {
    ui->dealButton->setEnabled(false);
    ui->bet1XButton->setEnabled(false);
    ui->bet2XButton->setEnabled(false);
    ui->bet3XButton->setEnabled(true);
    ui->bet4XButton->setEnabled(true);
    ui->checkButton->setEnabled(true);
    ui->foldButton->setEnabled(false);

    ui->anteSpinBox->setEnabled(false);
    ui->blindSpinBox->setEnabled(false);
    ui->tripSpinBox->setEnabled(false);

    ui->playBet->setText("");
}

void UltimateTexasHoldem::on_dealButton_clicked() {
    unsigned long long totalBets = ui->anteSpinBox->value() + ui->blindSpinBox->value() + ui->tripSpinBox->value();

    if (totalBets > player.money) {
        createWarningMessage("You do not have enough money!");
        return;
    }
    else if (totalBets + ui->anteSpinBox->value() > player.money) {
        createWarningMessage("You do not have enough to make a 1x Bet with the current bet setup!");
        return;
    }

    if (ui->tripSpinBox->value() > 0 && (ui->anteSpinBox->value()) <= 0) {
        createWarningMessage("You can not only place the trips bet.");
        return;
    }

    if (totalBets <= 1) {
        createWarningMessage("You must bet atleast 1 dollar.");
        return;
    }

    player.money -= totalBets;
    ui->money->setText(QString::number(player.money));
    setUiToInitalDeal();
    hideAllCards();
    dealCards();
    revealUserCards();
}


void UltimateTexasHoldem::on_checkButton_clicked()
{
    // At this point: Atleast the user cards are displayed.
    switch(numOfChecks) {
    case 0:
        ui->bet4XButton->setEnabled(false);
        ui->bet3XButton->setEnabled(false);
        ui->bet2XButton->setEnabled(true);
        revealThreeCommunityCard();
        ++numOfChecks;
        break;
    case 1:
        ui->bet2XButton->setEnabled(false);
        ui->checkButton->setEnabled(false);
        ui->bet1XButton->setEnabled(true);
        ui->foldButton->setEnabled(true);
        revealLastTwoCommunityCard();
        ++numOfChecks;
        break;
    case 2:
    {
        endRound();
        break;
    }

    default:
        qDebug() << "Check button pressed with more than three checks\n";
        break;
    }
}

void UltimateTexasHoldem::on_bet4XButton_clicked()
{
    if (betPlayAmount(ui->anteSpinBox->value() * 4)) {
        revealAllCommunityCards();
        endRound();
    }
}

void UltimateTexasHoldem::on_bet3XButton_clicked()
{
    if (betPlayAmount(ui->anteSpinBox->value() * 3)) {
        revealAllCommunityCards();
        endRound();
    }
}

void UltimateTexasHoldem::on_bet2XButton_clicked()
{
    if (betPlayAmount(ui->anteSpinBox->value() * 2)) {
        revealLastTwoCommunityCard();
        endRound();
    }
}

void UltimateTexasHoldem::on_bet1XButton_clicked()
{
    if (betPlayAmount(ui->anteSpinBox->value() * 1)) {
        endRound();
    }
}

void UltimateTexasHoldem::on_foldButton_clicked()
{
    endRound(true);
}


void UltimateTexasHoldem::slotEqualAnteBlindBoxes(int arg1)
{
    ui->anteSpinBox->setValue(arg1);
    ui->blindSpinBox->setValue(arg1);
}

void UltimateTexasHoldem::on_ResetMoney_clicked()
{
    player.money = 10000;
    ui->money->setText(QString::number(player.money));
}


//END OF SLOTS; START OF FUNCTIONS

/**
 * @brief UltimateTexasHoldem::betPlayAmount Function determine if the user is able to make the playBetAmount specified by it's argument
 *  If the player does the player's money is decreased by said amount, if not then a warning popup is given
 * @param playBetAmount The amount the player is trying to bet for the play back
 * @return A boolean indicating if the player was able to make the bet(true) or not(false)
 */
bool UltimateTexasHoldem::betPlayAmount(unsigned int playBetAmount) {
    if (playBetAmount > player.money) {
        createWarningMessage("You do not have enough money to make this bet!");
        return false;
    }

    player.money -= playBetAmount;
    ui->playBet->setText(QString::number(playBetAmount));
    ui->money->setText(QString::number(player.money));
    return true;
}


/**
 * @brief sleep Function sleeps the application for 850 seconds, note that all user inputs are delayed, they are not discarded.
 *   During this sleep period, the application still processes events, but delayed. Ensure to use filter objects before using this function.
 * @param msc The amount of miliseconds to sleep, default 850
 */
void sleep(int msc = 850) {
    QTime dieTime= QTime::currentTime().addMSecs(msc);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents, 100);
}

// Loop around for multiple qt versions either returning a qpixmap by a pointer or by a value
qint64 getCommunityCacheKey(const QPixmap& map) {
    return map.cacheKey();
}
qint64 getCommunityCacheKey(const QPixmap* const map) {
    return map->cacheKey();
}

/**
 * @brief UltimateTexasHoldem::revealThreeCommunityCard Function reveals the first three community cards in the UI
 * If the first card is set already on the UI, this function does nothing.
 */
void UltimateTexasHoldem::revealThreeCommunityCard() {
    // Already revealed, skip over this reveal.
    if (getCommunityCacheKey(ui->CommunityCard1->pixmap()) != backcard.cacheKey()) return;

    const std::vector<Card>& playerCards = player.hand.getCards();

    // Prevent any users from pressing any buttons while sleeping
    installEventFilter(filterMouseEvents);

    ui->CommunityCard1->setPixmap(getPixmapOfCard(playerCards[2]));
    sleep();
    ui->CommunityCard2->setPixmap(getPixmapOfCard(playerCards[3]));
    sleep();
    ui->CommunityCard3->setPixmap(getPixmapOfCard(playerCards[4]));

    removeEventFilter(filterMouseEvents);
}

/**
 * @brief UltimateTexasHoldem::revealLastTwoCommunityCard Function reveals the last two community cards in the UI
 * If the fourth card is already set on the UI, this function does nothing.
 */
void UltimateTexasHoldem::revealLastTwoCommunityCard() {
    // Already revealed, skip over this reveal.
    if (getCommunityCacheKey(ui->CommunityCard4->pixmap()) != backcard.cacheKey()) return;

    const std::vector<Card>& playerCards = player.hand.getCards();

    // Prevent any users from pressing any buttons while sleeping
    installEventFilter(filterMouseEvents);

    sleep();
    ui->CommunityCard4->setPixmap(getPixmapOfCard(playerCards[5]));
    sleep();
    ui->CommunityCard5->setPixmap(getPixmapOfCard(playerCards[6]));
    sleep();

    removeEventFilter(filterMouseEvents);
}

/**
 * @brief UltimateTexasHoldem::revealAllCommunityCards Function reveals all community cards in the UI
 */
void UltimateTexasHoldem::revealAllCommunityCards() {
    // Prevent any users from pressing any buttons during the sleep calls
    installEventFilter(filterMouseEvents);

    revealThreeCommunityCard();
    revealLastTwoCommunityCard();

    removeEventFilter(filterMouseEvents);
}

/**
 * @brief UltimateTexasHoldem::revealUserCards Function reveals all user cards in the UI
 */
void UltimateTexasHoldem::revealUserCards() {
    // Prevent any users
    installEventFilter(filterMouseEvents);

    const std::vector<Card>& playerCards = player.hand.getCards();

    ui->PlayerCard1->setPixmap(getPixmapOfCard(playerCards[0]));
    sleep();
    ui->PlayerCard2->setPixmap(getPixmapOfCard(playerCards[1]));

    removeEventFilter(filterMouseEvents);
}

/**
 * @brief UltimateTexasHoldem::revealDealerCards Function reveals all Dealer cards in the UI
 */
void UltimateTexasHoldem::revealDealerCards() {
    // Prevent any user's button presses
    installEventFilter(filterMouseEvents);

    const std::vector<Card>& houseCards = house.hand.getCards();

    ui->DealerCard1->setPixmap(getPixmapOfCard(houseCards[0]));
    sleep();
    ui->DealerCard2->setPixmap(getPixmapOfCard(houseCards[1]));
    sleep(1250); // sleep for a bit longer before showing the user who won
    removeEventFilter(filterMouseEvents);
}

/**
 * @brief UltimateTexasHoldem::hideAllCards Function hides all cards in the UI
 *  Each card (Community, Dealer, Player) cards are set to the backcard in the UI
 */
void UltimateTexasHoldem::hideAllCards() {
    ui->CommunityCard1->setPixmap(backcard);
    ui->CommunityCard2->setPixmap(backcard);
    ui->CommunityCard3->setPixmap(backcard);
    ui->CommunityCard4->setPixmap(backcard);
    ui->CommunityCard5->setPixmap(backcard);
    ui->DealerCard1->setPixmap(backcard);
    ui->DealerCard2->setPixmap(backcard);
    ui->PlayerCard1->setPixmap(backcard);
    ui->PlayerCard2->setPixmap(backcard);
}

/**
 * @brief UltimateTexasHoldem::dealCards Function first resets all hands of the dealer and house (rank + cards),
 *  and the deck gives out the cards to the house and player hands.
 */
void UltimateTexasHoldem::dealCards() {

    player.hand.clear();
    house.hand.clear();
    player.hand.rank = 0;
    house.hand.rank = 0;

    //Add players's 2 unique cards
    player.hand.addCard(deck.getCard());
    player.hand.addCard(deck.getCard());

    //Add house's 2 unique cards
    house.hand.addCard(deck.getCard());
    house.hand.addCard(deck.getCard());

    //Add community cards
    for (int i = 0; i < 5; i++) {
        Card communityCard = deck.getCard();

        player.hand.addCard(communityCard);
        house.hand.addCard(communityCard);
    }
}

/**
 * @brief UltimateTexasHoldem::useRoundResultService Function uses the round result service to determine who won and
 * the respective payoffs of winning/losing the round. Note that the round result service modifies player.money's
 * amount after winning/losing the round
 * @param playFolded Boolean flag indicating if the player folded his hand
 * @return A RoundResult object containing the information of who won and the payoffs applied to the player
 */
RoundResult UltimateTexasHoldem::useRoundResultService(bool playFolded) {
    static RoundResultService resultService(player, house); // variable only exists(staticly) in this scope

    // Play bet is in a generic text label, first must perform parsing to get the actual integral amount
    bool playBetExists = false;
    int playAmount = ui->playBet->text().toInt(&playBetExists);
    if (!playBetExists && ui->playBet->text() == "")
        playAmount = 0;
    else if (!playBetExists) {
        qDebug() << "No play bet? play bet should be set...";
        playAmount = 0;
    }

    // Delegate our ui elements's amounts to the service
    RoundResult roundResult = resultService.determineWinners(ui->anteSpinBox->value(), ui->blindSpinBox->value(), ui->tripSpinBox->value(), playAmount, playFolded);
    roundResult.playerRank = player.hand.rank;
    roundResult.dealerRank = house.hand.rank;
    return roundResult;
}

/**
 * @brief UltimateTexasHoldem::endRound Function peforms the sequential UI components that must be applied onto the UI
 *  When the round ends. It is expected for all community cards to be revealed(without dealers!), and
 *  functionr returns the UI back to the betting stage
 * @param folded Indicator variable if the player folded his hand
 */
void UltimateTexasHoldem::endRound(bool folded) {
    revealDealerCards();
    RoundResult roundResult = useRoundResultService(folded);
    createEndOfRoundDialog(roundResult);

    //update the ui with the player's calculated money
    ui->money->setText(QString::number(player.money));

    deck = Deck(); //reset the contents of the deck
    setUiToBetting();
}

/**
 * @brief UltimateTexasHoldem::getPixmapOfCard Function gets a QPixMap from a corresponding Card object. It is assumed the
 * card object is valid and the respective QPixmap is in the resource file.
 * @param card The card to get the respective pixmap of
 * @return  The pixmap of the card supplied
 */
QPixmap UltimateTexasHoldem::getPixmapOfCard(Card card) {
    QPixmap pixmap(QStringLiteral(":/cards/resources/%1%2.png").arg(card.value).arg(card.suit));
    return pixmap.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio);
}
