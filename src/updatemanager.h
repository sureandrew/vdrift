/************************************************************************/
/*                                                                      */
/* This file is part of VDrift.                                         */
/*                                                                      */
/* VDrift is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* VDrift is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with VDrift.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                      */
/************************************************************************/

#ifndef _UPDATEMANAGER_H
#define _UPDATEMANAGER_H

#include "autoupdate.h"
#include "game_downloader.h"
#include "cfg/config.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <memory>

class GUI;
class PATHMANAGER;
class Config;

class UPDATE_MANAGER
{
public:
	UPDATE_MANAGER(AUTOUPDATE & autoupdate, std::ostream & info, std::ostream & err);

	// returns true on success
	bool Init(
		const std::string & updatefilebase,
		const std::string & newupdatefile,
		const std::string & newupdatefilebackup,
		const std::string & guipage,
		const std::string & group);

	void Reset() {cur_object_id = 0;}

	void Increment() {cur_object_id++;}

	void Decrement() {cur_object_id--;}

	void Show(GUI & gui);

	void StartCheckForUpdates(GAME_DOWNLOADER downloader, GUI & gui);

	// returns true on success
	bool ApplyUpdate(GAME_DOWNLOADER downloader, GUI & gui, const PATHMANAGER & pathmanager);

	std::map<std::string, std::list <std::pair <std::string, std::string> > > & GetValueLists() {return valuelists;}

private:
	AUTOUPDATE & autoupdate;
	std::ostream & info_output;
	std::ostream & error_output;

	int cur_object_id;
	std::string updatefilebase;
	std::string updatefile;
	std::string updatefilebackup;
	std::string guipage;
	std::string group;

	// mirrors mappings used in the GUI, used to get the list of cars/tracks on disk
	std::map<std::string, std::list <std::pair <std::string, std::string> > > valuelists;

	// holds settings/updates.config from HEAD in the SVN data repository
	Config remoteconfig;

	// retrieve updates.config from HEAD in the SVN data repository and store it in remoteconfig
	// if remoteconfig is already set, returns true immediately
	// returns true on success
	bool DownloadRemoteConfig(GAME_DOWNLOADER downloader);
};

#endif
