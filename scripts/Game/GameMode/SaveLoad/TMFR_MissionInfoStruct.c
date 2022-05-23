class TMFR_MissionInfoStruct : JsonApiStruct {
	string name;
	string fileName;
	
	void TMFR_MissionInfoStruct()
	{
		RegV("name");
		RegV("fileName");
	}
}