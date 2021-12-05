#include "pch.h"
#include "ClientDlg.h"
#include <cstring>


//
//void SendMessage(CString userInput);
//{
//	do
//	{
//		//Prompt the user for some text
//		cout << ">";
//		getline(cin, userInput);
//		//Send the text
//		if (userInput.size() > 0)
//		{
//			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);		// Send the size
//			if (sendResult != SOCKET_ERROR)
//			{
//				//Wait for reponse
//				ZeroMemory(buf, 4096);					// Fills the block of memory by zero
//				int byteReceived = recv(sock, buf, 4096, 0);
//				if (byteReceived > 0)
//				{
//					//Echo reponse to console
//					cout << "SERVER>" << string(buf, 0, byteReceived) << endl;
//				}
//			}
//		}
//	} while (userInput.size() > 0);
//}


int sum()
{
	return 1 + 2;
}