void SwapMonsterType(int *oldmt)
{
	int mt;
	
	mt = *oldmt;
	if(currlevel == 16) {
		if(mt >= MT_NBLACK && mt <= MT_RBLACK) {
			mt = MT_XSKELAX;//MT_HELLHORROR;
		}
		if(mt == MT_CABALIST) {
			mt = MT_ADVOCATE;
		}
	}
	if(mt == MT_LTCHDMN) {
		mt = MT_STORM;
	}
	if(mt == MT_UDEDBLRG) {
		mt = MT_STORML;
	}
	if(mt == MT_REDDTH) {
		mt = MT_RSTORM;
	}

	*oldmt = mt;
}