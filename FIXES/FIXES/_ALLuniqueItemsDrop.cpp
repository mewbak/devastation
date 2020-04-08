//CheckUnique
	rv = random(29, numu);
	int k = 0;
	for(j = 0; j < sizeof(uok); j++) {
		if(!uok[j]) {
			continue;
		}
		if(k == rv) {
			break;
		}
		k++;
	}
	return j;