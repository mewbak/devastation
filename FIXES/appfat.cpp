void TraceErrorDD(HRESULT hError, char *pszBuffer, DWORD dwMaxChars)
{
	const char *szError;

	switch(hError) {
	case DD_OK:
		szError = "DD_OK";
		break;
	case DDERR_ALREADYINITIALIZED:
		szError = "DDERR_ALREADYINITIALIZED";
		break;
	case DDERR_BLTFASTCANTCLIP:
		szError = "DDERR_BLTFASTCANTCLIP";
		break;
	case DDERR_CANNOTATTACHSURFACE:
		szError = "DDERR_CANNOTATTACHSURFACE";
		break;
	case DDERR_CANNOTDETACHSURFACE:
		szError = "DDERR_CANNOTDETACHSURFACE";
		break;
	case DDERR_CANTCREATEDC:
		szError = "DDERR_CANTCREATEDC";
		break;
	case DDERR_CANTDUPLICATE:
		szError = "DDERR_CANTDUPLICATE";
		break;
	case DDERR_CLIPPERISUSINGHWND:
		szError = "DDERR_CLIPPERISUSINGHWND";
		break;
	case DDERR_COLORKEYNOTSET:
		szError = "DDERR_COLORKEYNOTSET";
		break;
	case DDERR_CURRENTLYNOTAVAIL:
		szError = "DDERR_CURRENTLYNOTAVAIL";
		break;
	case DDERR_DIRECTDRAWALREADYCREATED:
		szError = "DDERR_DIRECTDRAWALREADYCREATED";
		break;
	case DDERR_EXCEPTION:
		szError = "DDERR_EXCEPTION";
		break;
	case DDERR_EXCLUSIVEMODEALREADYSET:
		szError = "DDERR_EXCLUSIVEMODEALREADYSET";
		break;
	case DDERR_GENERIC:
		szError = "DDERR_GENERIC";
		break;
	case DDERR_HEIGHTALIGN:
		szError = "DDERR_HEIGHTALIGN";
		break;
	case DDERR_HWNDALREADYSET:
		szError = "DDERR_HWNDALREADYSET";
		break;
	case DDERR_HWNDSUBCLASSED:
		szError = "DDERR_HWNDSUBCLASSED";
		break;
	case DDERR_IMPLICITLYCREATED:
		szError = "DDERR_IMPLICITLYCREATED";
		break;
	case DDERR_INCOMPATIBLEPRIMARY:
		szError = "DDERR_INCOMPATIBLEPRIMARY";
		break;
	case DDERR_INVALIDCAPS:
		szError = "DDERR_INVALIDCAPS";
		break;
	case DDERR_INVALIDCLIPLIST:
		szError = "DDERR_INVALIDCLIPLIST";
		break;
	case DDERR_INVALIDDIRECTDRAWGUID:
		szError = "DDERR_INVALIDDIRECTDRAWGUID";
		break;
	case DDERR_INVALIDMODE:
		szError = "DDERR_INVALIDMODE";
		break;
	case DDERR_INVALIDOBJECT:
		szError = "DDERR_INVALIDOBJECT";
		break;
	case DDERR_INVALIDPARAMS:
		szError = "DDERR_INVALIDPARAMS";
		break;
	case DDERR_INVALIDPIXELFORMAT:
		szError = "DDERR_INVALIDPIXELFORMAT";
		break;
	case DDERR_INVALIDPOSITION:
		szError = "DDERR_INVALIDPOSITION";
		break;
	case DDERR_INVALIDRECT:
		szError = "DDERR_INVALIDRECT";
		break;
	case DDERR_LOCKEDSURFACES:
		szError = "DDERR_LOCKEDSURFACES";
		break;
	case DDERR_NO3D:
		szError = "DDERR_NO3D";
		break;
	case DDERR_NOALPHAHW:
		szError = "DDERR_NOALPHAHW";
		break;
	case DDERR_NOBLTHW:
		szError = "DDERR_NOBLTHW";
		break;
	case DDERR_NOCLIPLIST:
		szError = "DDERR_NOCLIPLIST";
		break;
	case DDERR_NOCLIPPERATTACHED:
		szError = "DDERR_NOCLIPPERATTACHED";
		break;
	case DDERR_NOCOLORCONVHW:
		szError = "DDERR_NOCOLORCONVHW";
		break;
	case DDERR_NOCOLORKEY:
		szError = "DDERR_NOCOLORKEY";
		break;
	case DDERR_NOCOLORKEYHW:
		szError = "DDERR_NOCOLORKEYHW";
		break;
	case DDERR_NOCOOPERATIVELEVELSET:
		szError = "DDERR_NOCOOPERATIVELEVELSET";
		break;
	case DDERR_NODC:
		szError = "DDERR_NODC";
		break;
	case DDERR_NODDROPSHW:
		szError = "DDERR_NODDROPSHW";
		break;
	case DDERR_NODIRECTDRAWHW:
		szError = "DDERR_NODIRECTDRAWHW";
		break;
	case DDERR_NOEMULATION:
		szError = "DDERR_NOEMULATION";
		break;
	case DDERR_NOEXCLUSIVEMODE:
		szError = "DDERR_NOEXCLUSIVEMODE";
		break;
	case DDERR_NOFLIPHW:
		szError = "DDERR_NOFLIPHW";
		break;
	case DDERR_NOGDI:
		szError = "DDERR_NOGDI";
		break;
	case DDERR_NOHWND:
		szError = "DDERR_NOHWND";
		break;
	case DDERR_NOMIRRORHW:
		szError = "DDERR_NOMIRRORHW";
		break;
	case DDERR_NOOVERLAYDEST:
		szError = "DDERR_NOOVERLAYDEST";
		break;
	case DDERR_NOOVERLAYHW:
		szError = "DDERR_NOOVERLAYHW";
		break;
	case DDERR_NOPALETTEATTACHED:
		szError = "DDERR_NOPALETTEATTACHED";
		break;
	case DDERR_NOPALETTEHW:
		szError = "DDERR_NOPALETTEHW";
		break;
	case DDERR_NORASTEROPHW:
		szError = "DDERR_NORASTEROPHW";
		break;
	case DDERR_NOROTATIONHW:
		szError = "DDERR_NOROTATIONHW";
		break;
	case DDERR_NOSTRETCHHW:
		szError = "DDERR_NOSTRETCHHW";
		break;
	case DDERR_NOT4BITCOLOR:
		szError = "DDERR_NOT4BITCOLOR";
		break;
	case DDERR_NOT4BITCOLORINDEX:
		szError = "DDERR_NOT4BITCOLORINDEX";
		break;
	case DDERR_NOT8BITCOLOR:
		szError = "DDERR_NOT8BITCOLOR";
		break;
	case DDERR_NOTAOVERLAYSURFACE:
		szError = "DDERR_NOTAOVERLAYSURFACE";
		break;
	case DDERR_NOTEXTUREHW:
		szError = "DDERR_NOTEXTUREHW";
		break;
	case DDERR_NOTFLIPPABLE:
		szError = "DDERR_NOTFLIPPABLE";
		break;
	case DDERR_NOTFOUND:
		szError = "DDERR_NOTFOUND";
		break;
	case DDERR_NOTLOCKED:
		szError = "DDERR_NOTLOCKED";
		break;
	case DDERR_NOTPALETTIZED:
		szError = "DDERR_NOTPALETTIZED";
		break;
	case DDERR_NOVSYNCHW:
		szError = "DDERR_NOVSYNCHW";
		break;
	case DDERR_NOZBUFFERHW:
		szError = "DDERR_NOZBUFFERHW";
		break;
	case DDERR_NOZOVERLAYHW:
		szError = "DDERR_NOZOVERLAYHW";
		break;
	case DDERR_OUTOFCAPS:
		szError = "DDERR_OUTOFCAPS";
		break;
	case DDERR_OUTOFMEMORY:
		szError = "DDERR_OUTOFMEMORY";
		break;
	case DDERR_OUTOFVIDEOMEMORY:
		szError = "DDERR_OUTOFVIDEOMEMORY";
		break;
	case DDERR_OVERLAYCANTCLIP:
		szError = "DDERR_OVERLAYCANTCLIP";
		break;
	case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
		szError = "DDERR_OVERLAYCOLORKEYONLYONEACTIVE";
		break;
	case DDERR_OVERLAYNOTVISIBLE:
		szError = "DDERR_OVERLAYNOTVISIBLE";
		break;
	case DDERR_PALETTEBUSY:
		szError = "DDERR_PALETTEBUSY";
		break;
	case DDERR_PRIMARYSURFACEALREADYEXISTS:
		szError = "DDERR_PRIMARYSURFACEALREADYEXISTS";
		break;
	case DDERR_REGIONTOOSMALL:
		szError = "DDERR_REGIONTOOSMALL";
		break;
	case DDERR_SURFACEALREADYATTACHED:
		szError = "DDERR_SURFACEALREADYATTACHED";
		break;
	case DDERR_SURFACEALREADYDEPENDENT:
		szError = "DDERR_SURFACEALREADYDEPENDENT";
		break;
	case DDERR_SURFACEBUSY:
		szError = "DDERR_SURFACEBUSY";
		break;
	case DDERR_SURFACEISOBSCURED:
		szError = "DDERR_SURFACEISOBSCURED";
		break;
	case DDERR_SURFACELOST:
		szError = "DDERR_SURFACELOST";
		break;
	case DDERR_SURFACENOTATTACHED:
		szError = "DDERR_SURFACENOTATTACHED";
		break;
	case DDERR_TOOBIGHEIGHT:
		szError = "DDERR_TOOBIGHEIGHT";
		break;
	case DDERR_TOOBIGSIZE:
		szError = "DDERR_TOOBIGSIZE";
		break;
	case DDERR_TOOBIGWIDTH:
		szError = "DDERR_TOOBIGWIDTH";
		break;
	case DDERR_UNSUPPORTED:
		szError = "DDERR_UNSUPPORTED";
		break;
	case DDERR_UNSUPPORTEDFORMAT:
		szError = "DDERR_UNSUPPORTEDFORMAT";
		break;
	case DDERR_UNSUPPORTEDMASK:
		szError = "DDERR_UNSUPPORTEDMASK";
		break;
	case DDERR_VERTICALBLANKINPROGRESS:
		szError = "DDERR_VERTICALBLANKINPROGRESS";
		break;
	case DDERR_WASSTILLDRAWING:
		szError = "DDERR_WASSTILLDRAWING";
		break;
	case DDERR_WRONGMODE:
		szError = "DDERR_WRONGMODE";
		break;
	case DDERR_XALIGN:
		szError = "DDERR_XALIGN";
		break;
	case DDERR_CANTLOCKSURFACE:
		szError = "DDERR_CANTLOCKSURFACE";
		break;
	case DDERR_CANTPAGELOCK:
		szError = "DDERR_CANTPAGELOCK";
		break;
	case DDERR_CANTPAGEUNLOCK:
		szError = "DDERR_CANTPAGEUNLOCK";
		break;
	case DDERR_DCALREADYCREATED:
		szError = "DDERR_DCALREADYCREATED";
		break;
	case DDERR_INVALIDSURFACETYPE:
		szError = "DDERR_INVALIDSURFACETYPE";
		break;
	case DDERR_NOMIPMAPHW:
		szError = "DDERR_NOMIPMAPHW";
		break;
	case DDERR_NOTPAGELOCKED:
		szError = "DDERR_NOTPAGELOCKED";
		break;
	default:
		const char szUnknown[] = "DDERR unknown 0x%x";
		/// ASSERT: assert(dwMaxChars >= sizeof(szUnknown) + 10);
		sprintf(pszBuffer, szUnknown, hError);
		return;
	}

	strncpy(pszBuffer, szError, dwMaxChars);
}

void TraceErrorDS(HRESULT hError, char *pszBuffer, DWORD dwMaxChars)
{
	const char *szError;

	switch(hError) {
	case DS_OK:
		szError = "DS_OK";
		break;
	case DSERR_ALLOCATED:
		szError = "DSERR_ALLOCATED";
		break;
	case DSERR_ALREADYINITIALIZED:
		szError = "DSERR_ALREADYINITIALIZED";
		break;
	case DSERR_BADFORMAT:
		szError = "DSERR_BADFORMAT";
		break;
	case DSERR_BUFFERLOST:
		szError = "DSERR_BUFFERLOST";
		break;
	case DSERR_CONTROLUNAVAIL:
		szError = "DSERR_CONTROLUNAVAIL";
		break;
	case DSERR_INVALIDCALL:
		szError = "DSERR_INVALIDCALL";
		break;
	case DSERR_INVALIDPARAM:
		szError = "DSERR_INVALIDPARAM";
		break;
	case DSERR_NOAGGREGATION:
		szError = "DSERR_NOAGGREGATION";
		break;
	case DSERR_NODRIVER:
		szError = "DSERR_NODRIVER";
		break;
	case DSERR_OUTOFMEMORY:
		szError = "DSERR_OUTOFMEMORY";
		break;
	case DSERR_PRIOLEVELNEEDED:
		szError = "DSERR_PRIOLEVELNEEDED";
		break;
	case E_NOINTERFACE:
		szError = "E_NOINTERFACE";
		break;
	default:
		const char szUnknown[] = "DSERR unknown 0x%x";
		/// ASSERT: assert(dwMaxChars >= sizeof(szUnknown) + 10);
		sprintf(pszBuffer, szUnknown, hError);
		return;
	}

	strncpy(pszBuffer, szError, dwMaxChars);
}