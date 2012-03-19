
#include "GameManager.h"
//#include <json/json.h>

//#pragma comment(lib, "json_vc71_libmtd.lib")

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, PSTR line, int show)
{
//	char* config_doc = "// Configuration options\
//{\
//    // Default encoding for text\
//    \"encoding\" : \"UTF-8\",\
//    \
//    // Plug-ins loaded at start-up\
//    \"plug-ins\" : [\
//        \"python\",\
//        \"c++\",\
//        \"ruby\"\
//        ],\
//        \
//    // Tab indent size\
//    \"indent\" : { \"length\" : 3, \"use_space\": true }\
//}";
//	
//	Json::Value root;   // will contains the root value after parsing.
//	Json::Reader reader;
//	bool parsingSuccessful = reader.parse( config_doc, root );
//	if ( !parsingSuccessful )
//	{
//		// report to the user the failure and their locations in the document.
//		std::cout  << "Failed to parse configuration\n";
//		return 0;
//	}
//
//	// Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
//	// such member.
//	std::string encoding = root.get("encoding", "UTF-8" ).asString();
//	// Get the value of the member of root named 'encoding', return a 'null' value if
//	// there is no such member.
//	const Json::Value plugins = root["plug-ins"];

	CGameManager::GetGameManager().Init(hInst);

	CGameManager::GetGameManager().Run();

	return 0;
}