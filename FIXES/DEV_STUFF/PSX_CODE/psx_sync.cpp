//debug psx sync item ?
void sync_unk_8028230C(int pnum, TSyncHeader *p)
{
	int ii;
	ItemStruct *pItem;
	
	if(p->bItemI != 255) {
		if(p->wItemIndx != item[p->bItemI].IDidx
		|| p->wItemCI != item[p->bItemI]._iCreateInfo
		|| p->dwItemSeed != item[p->bItemI]._iSeed) {
			ii = FindGetItem(p->wItemIndx, p->wItemCI, p->dwItemSeed);
			if(ii == -1) {
				SyncPutItem(
					pnum,
					p->bItemX,
					p->bItemY,
					p->wItemIndx,
					p->wItemCI,
					p->dwItemSeed,
					p->bItemId,
					p->bItemDur,
					p->bItemMDur,
					p->bItemCh,
					p->bItemMCh,
					p->wItemVal,
					p->dwItemBuff);
			}
		}
	}
	if(p->bPInvLoc != 255) {
		pItem = &plr[myplr].InvBody[p->bPInvLoc];
		if(p->wPInvIndx != pItem->IDidx
		|| p->wPInvCI != pItem->_iCreateInfo
		|| p->dwPInvSeed != pItem->_iSeed
		|| p->bPInvId != pItem->_iIdentified) {
			CheckInvSwap(pnum, p->bPInvLoc, p->wPInvIndx, p->wPInvCI, p->dwPInvSeed, p->bPInvId);
		}
	}
}
