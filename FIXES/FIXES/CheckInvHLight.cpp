CheckInvHLight

		if(pi->_itype == -1 || pi->_iLoc != 2) {
			rv = 5;
			pi = &p->InvBody[5];
		} else {
			rv = 4;
		}

flip condional, check beta