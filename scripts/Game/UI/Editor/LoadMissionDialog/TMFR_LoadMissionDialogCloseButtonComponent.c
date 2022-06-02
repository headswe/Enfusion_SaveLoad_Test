class TMFR_LoadMissionCloseButtonComponent : ScriptedWidgetComponent {
	override bool OnClick(Widget w, int x, int y, int button) {
		TMFR_UIManagerComponent comp = TMFR_UIManagerComponent.GetInstance();
		if(!comp)
			return false;
		comp.CloseLoadDialog();
		return true;
	}
}