Chess
Designed and coded By:
Noam Celermajer
Shahak
Preface and explanation 
This is a chess game for two human (AI) comming soon...
This game is Splited to two part :
1: BackEnd (Engine) calculate move (and later also AI)
2: FrontEnd Get Manage all the Graphics and user's Inputs

BackEnd(Engine):
	The Chess is divide in Classes see DesignChess.pdf (by shahak).
	
	Classes:
		Game:
			recolting Board and make the game we can call it the Main of our game
		Board:
			Manage the board[8][8] (Generate etc...)
		Piece:
			Manage the piece {King, Queen, Rook, Bishop, Pawn, Knight, Empty}
	
	The BackEnd communicate(talk) with the FrontEnd via Pipes :
								* Named pipe is a mechanism for one-way or bi-directional inter-process 
								* communication between the pipe server and one or more pipe clients in the
								* local machine or across the computers in the intranet:
FrontEnd(GUI)
	Coded in c# nothing really important if interested contact me :noam.celermajer@gmail.com

