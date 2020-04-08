static void game_logic()
{
	int Frames, ThisTick, SinceLast;

	if (PauseMode != '\0') {
		return;
	}

//
	if (GameSpeed == GM_SLOW) {
		Frames = 3;
	} else if (GameSpeed == GM_FAST) {
		Frames = 2;
	} else {
		DBG_Error(NULL, "source/DIABLO.cpp", 3197);
		Frames = 1;
	}
//

	if (sgnTimeoutCurs == 0) {
		CheckCursMove();
	}

//
	ThisTick = VID_GetTick();
	SinceLast = Frames;
	if (LastFrCount != -1) {
		SinceLast = ThisTick - LastFrCount;
	}
	if (SinceLast > 5) {
		SinceLast = 5;
	}
	if (SinceLast < Frames) {
		return;
	}
//

	if (demo_pad_time != 0) {
		PAD_Handler();
	}
	if (gbProcessPlayers != '\0') {
		ProcessPlayers();
	}
	if (leveltype == 0) {
		FUN_8003b518();
		FUN_800458cc();
		func_0x8005d434();
		func_0x800bc838();
		func_0x8015a694();
	}
	else {
		FUN_801549e4();
		FUN_800554dc();
		FUN_8014a694();
		FUN_800458cc();
		FUN_8004d434();
		FUN_8004d754();
	}
	func_0x8004d8c8();
	if (DAT_800da555 != '\0') {
		myplr = 0;
		func_0x80086ac8(0);
	}
	if (DAT_800dbf3d != '\0') {
		myplr = 1;
		func_0x80086ac8(1);
	}
	myplr = 0;
	func_0x800774f4();
	LastFrCount = ThisTick - (SinceLast - Frames);
	force_redraw |= 1;
}
