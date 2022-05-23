class TMFR_MissionStruct : JsonApiStruct {
	ref array<ref TMFR_MissionInfoStruct> missions = {};
	void AddMission(string name, string fileName) {
		TMFR_MissionInfoStruct mission = new TMFR_MissionInfoStruct();
		mission.name = name;
		mission.fileName = fileName;
		missions.Insert(mission);
	}
	void TMFR_MissionStruct() {
		RegV("missions");
	}
}