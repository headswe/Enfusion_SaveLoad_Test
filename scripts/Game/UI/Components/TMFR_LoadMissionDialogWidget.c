class TMFR_LoadMissionDialogWidget : ScriptedWidgetComponent {
	ResourceName ItemLayout = "{61B1BAFC2102D790}UI/layouts/Editor/MissionList/LoadMissionItemRow.layout";
	Widget m_Widget;
	VerticalLayoutWidget m_TableBody;
	protected ref array<Widget> items = {};
	override void HandlerAttached(Widget w) {
		m_Widget = w;
		m_TableBody = VerticalLayoutWidget.Cast(m_Widget.FindAnyWidget("TableBody"));
		if (SCR_Global.IsEditMode()) {
			TMFR_MissionInfoStruct mission = new TMFR_MissionInfoStruct();
			mission.fileName = "test.json";
			mission.name = "Blazing Saddels";
			AddMissionRow(mission);
			return;
		}
		TMFR_SaveLoadComponent comp = TMFR_SaveLoadComponent.GetInstance();
		foreach(TMFR_MissionInfoStruct mission : comp.missionsStruct.missions) {
			AddMissionRow(mission);
		}
	}
	override bool OnKeyPress(Widget w, int x, int y, int key) {
		if(KeyCode.KC_ESCAPE != key)
			return false;
		TMFR_EditorUIManagerComponent comp = TMFR_EditorUIManagerComponent.GetInstance();
		if(!comp)
			return false;
		comp.CloseLoadDialog();
		return true;
	}
	void AddMissionRow(TMFR_MissionInfoStruct mission) {
		Widget item = GetGame().GetWorkspace().CreateWidgets(ItemLayout, m_TableBody);
		items.Insert(item);
		ButtonWidget button = ButtonWidget.Cast(item.FindAnyWidget("LoadButton"));
		TMFR_MissionListItemLoadButtonComponent comp = new TMFR_MissionListItemLoadButtonComponent();
		comp.missionStruct = mission;
		button.AddHandler(comp);
		TextWidget t = TextWidget.Cast(item.FindAnyWidget("MissionName"));
		t.SetText(mission.name);
		item.Update();
	}
}