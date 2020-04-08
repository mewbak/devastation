// doesnt fix hellfire
int FindValidShrine(int i)
{
	int rv;
	BOOL done;

	done = FALSE;
	do {
		do {
			rv = random(0, 26);
			if(currlevel >= shrinemin[rv] && currlevel <= shrinemax[rv] && rv != 8) {
				done = TRUE;
			}
		} while(!done);
		done = TRUE;
        if (gbMaxPlayers != 1 && shrineavail[rv] == 1) {
            done = FALSE;
        }
		if (gbMaxPlayers == 1 && shrineavail[rv] == 2) {
			done = FALSE;
		}
	} while(!done);

	return rv;
}