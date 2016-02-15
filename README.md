######################################################
cuPID: Carleton University Project Partner Identifier
######################################################


              #######  ########  #######
              ##   ###    ##     ##     ##
 ####  #    # #######     ##     ##      ##
#      #    # ##          ##     ##      ##
#      #    # ##          ##     ##      ##
#      #    # ##          ##     ##     ##
 ####   ####  ##       ########  #######



[![cuPID Demo](https://youtu.be/vMsCENg2PTc)](https://youtu.be/vMsCENg2PTc)
------------------------------------------------
    What's New in cuPID 2.0
------------------------------------------------
- New user's answer coding Question before new account is saved in database.
  This feature is used for technical score normalization as explained in the
  document. (SEE END OF FILE!!!!)
- New Settings section added for user to personalize cuPID experience by
  changing colors and Fonts.
- Administrator User can now create teams from the students currently registered
  in their created project. Match summary is provided, and Detailed explanation
  of match results is available with the click of a button.
  See Revisions section at the end of design document to get a
  quick glimpse of what changed in our algorithm. Hint… Nothing :)
- Recent Project section added to side bar to keep track of the last 3 projects
  a user has executed an action on.
- Better fault tolerance and error detection for great user experience.
- General User Interface tweaks to enhance user experience for application.
------------------------------------------------


------------------------------------------------
Installation Instructions
------------------------------------------------
##Setup##
cuPID is brought to you by the insomnia team.
In order to launch this product, you must have the Qt Framework installed.
The following steps stipulate installation instructions for the user:
- untar cuPID source code: tar -xvf cuPID.tar
- ensure that the Data directory is in the same path as the cuPID directory
  Hence, after untar, your directory should look like this:
  - cuPID Data
- Open cuPID project with Qt
- Select build directory:
  - on opening the application with Qt, you will be prompted
    to configure the build settings of the project
  - Ensure the Debug directory and Release directories are in the same
    path as the cuPID directory
- Save the configuration and build the qt cuPID project
  After configuration, your directory should look like this:
  - cuPID, Data, build-cuPID-Desktop-Debug

##Code Checker Integration##
- Call us paranoid, but we want to ensure the best user experience. In order to
  ensure that the code checking feature works seamlessly, we will need you to
  do a little check for us.
  - look into the code checker directory from the command line
    (cd cuPID/codeChecker)
  - check that the permissions of the codeChecker.sh script is
    executable (ls -al codeChecker.sh)
  - If all is well, you should see something like this at the start of the line:
    -rwxr-xr-x
  - If not, please run this command in your command line
    (This assumes you are currently in the codeChecker directory)
    chmod 777 codeChecker.sh
  - Once all this is done, you are all set
------------------------------------------------

###################################################################
Data Filled Information for Testing Features
###################################################################
Username        LoginType
Leo               Admin     (Owner of all projects in the db at the moment)
Jman              Admin
Jojo              Admin
Bud               Admin
Tommy             Admin
Roxy              Student
Seb               Student
Ju                Student
Mich              Student
Derek123          Student
JF                Student
SS                Student
charles           Student
dabby             Student
pseguin           Student
tomR              Student
bran              Student
ashleigh          Student
bri               Student
imDonna           Student
jess              Student
mikey             Student
harv              Student
lewis             Student
amy               Student
raj               Student
howie             Student
shelby            Student
penny             Student
lenny             Student
###################################################################

We are exited to deliver the final cuPID system.
Hope you enjoy.

Yours truly, the insomnia team :)


###############################################################################
###############################################################################
###############################################################################
###############################################################################
To Bypass Coding question (This is just for testing only)
Insert the following code into the coding textview to get the max possible mark

void maximumThreeNumbersInList(int*list, int count, int*maxThree)
{
	maxThree[0] = -999999;
	maxThree[1] = -999999;
	maxThree[2] = -999999;
	for (int i = 0; i < count; i++)
	{
		if (list[i] > maxThree[0])
		{
			maxThree[2] = maxThree[1];
			maxThree[1] = maxThree[0];
			maxThree[0] = list[i];
		}
		else if(list[i] > maxThree[1])
		{
			maxThree[2] = maxThree[1];
			maxThree[1] = list[i];
		}
		else if(list[i] > maxThree[2])
		{
			maxThree[2] = list[i];
		}
	}
}
###############################################################################
###############################################################################
###############################################################################
###############################################################################
