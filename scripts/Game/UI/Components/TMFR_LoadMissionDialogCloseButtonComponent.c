class TMFR_LoadMissionCloseButtonComponent : ScriptedWidgetComponent {
	override bool OnClick(Widget w, int x, int y, int button) {
		TMFR_EditorUIManagerComponent comp = TMFR_EditorUIManagerComponent.GetInstance();
		if(!comp)
			return false;
		comp.CloseLoadDialog();
		return true;
	}
}