// Script to add a desktop shortcut
// From https://stackoverflow.com/questions/21956108/qt-installer-framework-create-shortcut-on-the-desktop
Component.prototype.createOperations = function()
{
    try {
        // call the base create operations function
        component.createOperations();
        if (installer.value("os") == "win") { 
            try {
                var userProfile = installer.environmentVariable("USERPROFILE");
                installer.setValue("UserProfile", userProfile);
                component.addOperation("CreateShortcut", "@TargetDir@\\UltimateTexasHoldem.exe", "@UserProfile@\\Desktop\\UltimateTexasHoldem.lnk");
            } catch (e) {
                // Do nothing if key doesn't exist
            }
        }
    } catch (e) {
        print(e);
    }
}