[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class TMFR_SaveLoadComponentClass: SCR_BaseGameModeComponentClass
{
};
/*!
Manager for saving and loading game mode data.

ToDo:
* Load when starting the world if it's requested (i.e., 'Continue' save)
* Refactor Conflict save to use this system
*/
class TMFR_SaveLoadComponent: SCR_BaseGameModeComponent
{
	[Attribute(desc: "Struct object which manages saved data. Must be defined, without it saving won't work.")]
	protected ref SCR_MissionStruct m_Struct;
	ref TMFR_MissionStruct missionsStruct = new TMFR_MissionStruct();
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
		return "$profile:missions\\"+m_sFileName+".json";
	}
	
	string GetMissionsPath() {
		return "$profile:missions\\missions.json";
	}
	override void OnPostInit(IEntity owner) {
	}
	void Save()
	{
		FileIO.MakeDirectory("$profile:missions");
		m_Struct.Serialize();
		m_Struct.SaveToFile(GetFullPath());
		TMFR_MissionInfoStruct exists;
		foreach(TMFR_MissionInfoStruct m : missionsStruct.missions) {
			if(m.fileName == m_sFileName+".json")
				exists = m;
		}
		if(exists == null)
			missionsStruct.AddMission("testing", m_sFileName+".json");
		SaveMissions();
	}
	void Load()
	{
		if(!FileIO.FileExist(GetFullPath()))
			return;
		m_Struct.LoadFromFile(GetFullPath());
		m_Struct.Deserialize();
	}
	void SaveMissions() {
		FileIO.MakeDirectory("$profile:missions");
		missionsStruct.SaveToFile(GetMissionsPath());
	}
	void LoadMissions() {
		if(!FileIO.FileExist(GetMissionsPath()))
			return;
		missionsStruct.LoadFromFile(GetMissionsPath());
		int k = 0;
	}
	override void OnWorldPostProcess(World world)
	{
		LoadMissions();
	}
};