modded enum ChimeraMenuPreset : ScriptMenuPresetEnum {
	MissionSaveDialog,
	MissionLoadDialog
}

[ComponentEditorProps(category: "GameScripted/Editor", description: "", icon: "WBData/ComponentEditorProps/componentEditor.png")]
class TMFR_UIManagerComponentClass: SCR_BaseEditorComponentClass
{
};

class TMFR_UIManagerComponent : ScriptComponent
{
	protected MenuBase m_LoadDialog;
	protected MenuBase m_SaveDialog;
	protected MenuManager m_MenuManager;
	
	protected ResourceName m_LoadDialogLayout = "{313CE55773C7A138}UI/layouts/Editor/LoadMissionDialog/TMFR_LoadMissionDialog.layout";
	protected ResourceName m_SaveDialogLayout = "{5A4229D1E23B06A7}UI/layouts/Editor/SaveMissionDialog/TMFR_SaveMissionDialog.layout";
	
	protected static TMFR_UIManagerComponent m_Instance;
	static TMFR_UIManagerComponent GetInstance()
	{
		return m_Instance;
	}
	
	void TMFR_UIManagerComponent() {
		m_Instance = this;
	}
	override void OnPostInit(IEntity owner) {
		m_MenuManager = GetGame().GetMenuManager();
		if(!Replication.IsClient())
			return;
		GetGame().GetCallqueue().Call(RequestMissions);
	}
	void RequestMissions() {
		Rpc(RpcAsk_SyncMissions);
	}
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void RpcAsk_SyncMissions() {
		TMFR_ScenarioDatabaseStruct mStruct = TMFR_SaveLoadComponent.GetInstance().missionsStruct;
		array<string> missionNames = {};
		array<string> fileNames = {};
		foreach( TMFR_ScenarioStruct m : mStruct.missions) {
			missionNames.Insert(m.name);
			fileNames.Insert(m.fileName);
		}
		Rpc(RpcDo_ReceiveMissions, missionNames, fileNames);
	}
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)] // this is proper workaround but fuck it :)
	void RpcDo_ReceiveMissions(array<string> missionNames, array<string> fileNames) 
	{
		Print("Received stuff");
		TMFR_ScenarioDatabaseStruct mstruct = TMFR_SaveLoadComponent.GetInstance().missionsStruct;
		int length = missionNames.Count();
		for(int i = 0; i < length; i++) {
			TMFR_ScenarioStruct info = new TMFR_ScenarioStruct();
			info.name = missionNames[i];
			info.fileName = fileNames[i];
			mstruct.missions.Insert(info);
		}
	}
	void OpenLoadDialog() {
		m_LoadDialog = m_MenuManager.OpenDialog(ChimeraMenuPreset.MissionLoadDialog, DialogPriority.CRITICAL);
	}
	void CloseLoadDialog() {
		if(!m_LoadDialog) {
			Print("No menu?");
			return;
		}
		m_LoadDialog.Close();
		m_LoadDialog = null;
	}
	void OpenSaveDialog() {
		m_SaveDialog = m_MenuManager.OpenDialog(ChimeraMenuPreset.MissionSaveDialog, DialogPriority.CRITICAL);
	}
	void CloseSaveDialog() {
		if(!m_SaveDialog) {
			Print("No menu?");
			return;
		}
		m_SaveDialog.Close();
	}
	void Save(string name, string fileName)
	{
		if(Replication.IsClient()) 
		{
			Rpc(RpcAsk_Save, name, fileName);
			return;
		}
		TMFR_SaveLoadComponent.GetInstance().Save(name, fileName);
	}
	void Load(string fileName)
	{
		if(Replication.IsClient()) 
		{
			Rpc(RpcAsk_Load, fileName);
			return;
		}
		TMFR_SaveLoadComponent.GetInstance().Load(fileName);
	}
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void RpcAsk_Save(string name, string fileName) {
		TMFR_SaveLoadComponent.GetInstance().Save(name, fileName);
	}
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void RpcAsk_Load(string fileName) {
		TMFR_SaveLoadComponent.GetInstance().Load(fileName);
	}
};