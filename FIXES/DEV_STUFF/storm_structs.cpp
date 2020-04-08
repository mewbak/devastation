void sub_6FFBC544(
	HANDLE hLog,
	_SNETPROGRAMDATA *programdata,
	_SNETPLAYERDATA *playerdata,
	_SNETUIDATA *interfacedata,
	_SNETVERSIONDATA *versiondata)
{
	if(programdata != NULL && programdata->size >= 0x3C) {
		SLogWrite(hLog, "  programdata.size                    = %u",     programdata->size);
		SLogWrite(hLog, "  programdata.programname             = \"%s\"", programdata->programname);
		SLogWrite(hLog, "  programdata.programdescription      = \"%s\"", programdata->programdescription);
		SLogWrite(hLog, "  programdata.programid               = 0x%08x", programdata->programid);
		SLogWrite(hLog, "  programdata.versionid               = 0x%08x", programdata->versionid);
		SLogWrite(hLog, "  programdata.reserved1               = %u",     programdata->reserved1);
		SLogWrite(hLog, "  programdata.maxplayers              = %u",     programdata->maxplayers);
		SLogWrite(hLog, "  programdata.initdata                = 0x%08x", programdata->initdata);
		SLogWrite(hLog, "  programdata.initdatabytes           = %u",     programdata->initdatabytes);
		SLogWrite(hLog, "  programdata.reserved2               = 0x%08x", programdata->reserved2);
		SLogWrite(hLog, "  programdata.optcategorybits         = 0x%08x", programdata->optcategorybits);
		SLogWrite(hLog, "  programdata.cdkey                   = \"%s\"", programdata->cdkey);
		SLogWrite(hLog, "  programdata.registereduser          = \"%s\"", programdata->registereduser);
		SLogWrite(hLog, "  programdata.spawned                 = %u",     programdata->spawned);
		SLogWrite(hLog, "  programdata.lcid                    = 0x%08x", programdata->lcid);
	}
	if(playerdata != NULL && playerdata->size >= 0x10) {
		SLogWrite(hLog, "  playerdata.size                     = %u",     playerdata->size);
		SLogWrite(hLog, "  playerdata.playername               = \"%s\"", playerdata->playername);
		SLogWrite(hLog, "  playerdata.playerdescription        = \"%s\"", playerdata->playerdescription);
	}
	if(interfacedata != NULL && interfacedata->size >= 0x50) {
		SLogWrite(hLog, "  interfacedata.size                  = %u",     interfacedata->size);
		SLogWrite(hLog, "  interfacedata.uiflags               = 0x%08x", interfacedata->uiflags);
		SLogWrite(hLog, "  interfacedata.parentwindow          = 0x%08x", interfacedata->parentwindow);
		SLogWrite(hLog, "  interfacedata.artcallback           = 0x%08x", interfacedata->artcallback);
		SLogWrite(hLog, "  interfacedata.authcallback          = 0x%08x", interfacedata->authcallback);
		SLogWrite(hLog, "  interfacedata.createcallback        = 0x%08x", interfacedata->createcallback);
		SLogWrite(hLog, "  interfacedata.drawdesccallback      = 0x%08x", interfacedata->drawdesccallback);
		SLogWrite(hLog, "  interfacedata.selectedcallback      = 0x%08x", interfacedata->selectedcallback);
		SLogWrite(hLog, "  interfacedata.messageboxcallback    = 0x%08x", interfacedata->messageboxcallback);
		SLogWrite(hLog, "  interfacedata.soundcallback         = 0x%08x", interfacedata->soundcallback);
		SLogWrite(hLog, "  interfacedata.statuscallback        = 0x%08x", interfacedata->statuscallback);
		SLogWrite(hLog, "  interfacedata.getdatacallback       = 0x%08x", interfacedata->getdatacallback);
		SLogWrite(hLog, "  interfacedata.categorycallback      = 0x%08x", interfacedata->categorycallback);
		SLogWrite(hLog, "  interfacedata.categorylistcallback  = 0x%08x", interfacedata->categorylistcallback);
		SLogWrite(hLog, "  interfacedata.newaccountcallback    = 0x%08x", interfacedata->newaccountcallback);
		SLogWrite(hLog, "  interfacedata.profilecallback       = 0x%08x", interfacedata->profilecallback);
		SLogWrite(hLog, "  interfacedata.profilefields         = 0x%08x", interfacedata->profilefields);
		SLogWrite(hLog, "  interfacedata.profilebitmapcallback = 0x%08x", interfacedata->profilebitmapcallback);
		SLogWrite(hLog, "  interfacedata.selectnamecallback    = 0x%08x", interfacedata->selectnamecallback);
		SLogWrite(hLog, "  interfacedata.changenamecallback    = 0x%08x", interfacedata->changenamecallback);
	}
	if(versiondata != NULL && versiondata->size >= 0x14) {
		SLogWrite(hLog, "  versiondata.size                    = %u",     versiondata->size);
		SLogWrite(hLog, "  versiondata.versionstring           = \"%s\"", versiondata->versionstring);
		SLogWrite(hLog, "  versiondata.executablefile          = \"%s\"", versiondata->executablefile);
		SLogWrite(hLog, "  versiondata.originalarchivefile     = \"%s\"", versiondata->originalarchivefile);
		SLogWrite(hLog, "  versiondata.patcharchivefile        = \"%s\"", versiondata->patcharchivefile);
	}
}