class TMFR_ScenarioDatabaseStruct : JsonApiStruct {
	ref array<ref TMFR_ScenarioStruct> missions = {};
	void AddMission(string name, string fileName) {
		TMFR_ScenarioStruct mission = new TMFR_ScenarioStruct();
		mission.name = name;
		mission.fileName = fileName;
		missions.Insert(mission);
	}
	void TMFR_ScenarioDatabaseStruct() {
		RegV("missions");
	}
}