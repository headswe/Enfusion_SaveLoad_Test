class TMFR_MissionListItemLoadButtonComponent : ScriptedWidgetComponent {
	Widget m_Widget;
	TMFR_ScenarioStruct missionStruct;
	override void HandlerAttached(Widget w) {
		m_Widget = w;
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		if(missionStruct) {
			TMFR_UIManagerComponent comp = TMFR_UIManagerComponent.GetInstance();
			if(!comp)
				return false;
			comp.Load(missionStruct.fileName);
			comp.CloseSaveDialog();
		}
		return true;
	}
}