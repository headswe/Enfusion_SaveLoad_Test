[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class TMFR_SaveLoadComponentClass: SCR_BaseGameModeComponentClass
{
};

class TMFR_SaveLoadComponent: SCR_BaseGameModeComponent
{
	[Attribute(desc: "Struct object which manages saved data. Must be defined, without it saving won't work.")]
	protected ref TMFR_MissionStruct m_Struct;
	ref TMFR_ScenarioDatabaseStruct missionsStruct = new TMFR_ScenarioDatabaseStruct();
	string m_sFileName = "WB_TESTING";
	
	static TMFR_SaveLoadComponent GetInstance()
	{
		BaseGameMode gameMode = GetGame().GetGameMode();
		if (gameMode)
			return TMFR_SaveLoadComponent.Cast(gameMode.FindComponent(TMFR_SaveLoadComponent));
		else
			return null;
	}
	string GetFullPath() {
		return GetFullPath(m_sFileName);
	}
	string GetFullPath(string fileName) {
		return "$profile:missions\\"+fileName+".json";
	}
	
	string GetMissionsPath() {
		return "$profile:missions\\missions.json";
	}
	override void OnPostInit(IEntity owner) {
	}
	
	void Save(string name, string fileName)
	{
		Print("Save: " + fileName);
		FileIO.MakeDirectory("$profile:missions");
		m_Struct.Serialize();
		m_Struct.SaveToFile(GetFullPath(fileName));
		TMFR_ScenarioStruct exists;
		foreach(TMFR_ScenarioStruct m : missionsStruct.missions) {
			if(m.fileName == fileName+".json")
				exists = m;
		}
		if(exists == null)
			missionsStruct.AddMission(name, fileName+".json");
		SaveMissions();
	}
	void Load(string fileName)
	{
		if(!FileIO.FileExist("$profile:missions\\"+fileName))
			return;
		m_Struct.LoadFromFile("$profile:missions\\"+fileName);
		m_Struct.Deserialize();
	}

	void SaveMissions() {
		Print("SaveMissions");
		FileIO.MakeDirectory("$profile:missions");
		missionsStruct.SaveToFile(GetMissionsPath());
	}
	void LoadMissions() {
		if(!FileIO.FileExist(GetMissionsPath()))
			return;
		missionsStruct.LoadFromFile(GetMissionsPath());
		Print("LoadMissions file");
	}
	override void OnWorldPostProcess(World world)
	{
		if(Replication.IsClient())
			return;
		LoadMissions();
	}
};