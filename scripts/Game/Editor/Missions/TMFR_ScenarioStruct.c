class TMFR_ScenarioStruct : JsonApiStruct {
	string name;
	string fileName;
	
	void TMFR_ScenarioStruct()
	{
		RegV("name");
		RegV("fileName");
	}
}