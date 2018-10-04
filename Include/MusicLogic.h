// ******** MusicLogic.h **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 10/1/18
// Description: Header file for MusicLogic.c
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 10/1/18
// Hardware Configuration: N/A

#ifndef MUSIC_PLAYER_H_
#define MUSIC_PLAYER_H_

typedef enum{
	PlayPause,
	Rewind,
	ChangeInstrument,
	ChangeTempo,
	NumMusicPlayerButtons
} MusicPlayerButton;

void MusicPlayerShouldUpdate(MusicPlayerButton button);

#endif // MUSIC_PLAYER_H_
