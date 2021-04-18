// Script to add a desktop shortcut
// From https://stackoverflow.com/questions/21956108/qt-installer-framework-create-shortcut-on-the-desktop

function Component()
{
    
}

Component.prototype.createOperations = function()
{
    try {
        // call the base create operations function
        component.createOperations();
        if (installer.value("os") == "win") { 
            try {
                var userProfile = installer.environmentVariable("USERPROFILE");
                installer.setValue("UserProfile", userProfile);
                component.addOperation("CreateShortcut", 
                            "@TargetDir@/UltimateTexasHoldem.exe",// target
                            "@DesktopDir@/Ultimate Texas Holdem.lnk",// link-path
                            "workingDirectory=@TargetDir@",// working-dir
                            "iconPath=@TargetDir@/UltimateTexasHoldem.exe", "iconId=0",// icon
                            "description=Start Ultimate Texas Holdem");// description
            } catch (e) {
                // Do nothing if key doesn't exist
            }
        }
    } catch (e) {
        print(e);
    }
}
