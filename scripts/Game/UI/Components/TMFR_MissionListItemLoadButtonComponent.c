class TMFR_MissionListItemLoadButtonComponent : ScriptedWidgetComponent {
	Widget m_Widget;
	TMFR_MissionInfoStruct missionStruct;
	override void HandlerAttached(Widget w) {
		m_Widget = w;
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		Print("FUck");
		if(missionStruct)
			Print(missionStruct.name);
		return true;
	}
}