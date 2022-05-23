class TMFR_SaveMissionCloseButtonComponent : ScriptedWidgetComponent {
	override bool OnClick(Widget w, int x, int y, int button) {
		TMFR_SaveMissionDialogComponent comp = TMFR_SaveMissionDialogComponent.GetInstance();
		if(!comp)
			return false;
		comp.OnCloseClicked();
		return true;
	}
}