class TMFR_SaveMissionDialogComponent : ScriptedWidgetComponent {
	Widget m_Widget;
	EditBoxWidget missionNameEditBox;
	EditBoxWidget missionFileNameEditBox;
	protected static TMFR_SaveMissionDialogComponent m_Instance;
	static TMFR_SaveMissionDialogComponent GetInstance() {
		return m_Instance;
	}
	void TMFR_SaveMissionDialogComponent() {
		m_Instance = this;
	}
	override void HandlerAttached(Widget w) {
		m_Widget = w;
		missionNameEditBox = EditBoxWidget.Cast(w.FindAnyWidget("MissionNameEditBox"));
		missionFileNameEditBox = EditBoxWidget.Cast(w.FindAnyWidget("MissionFileNameEditBox"));
	}
	void OnSaveClicked() {
		TMFR_EditorUIManagerComponent comp = TMFR_EditorUIManagerComponent.GetInstance();
		if(!comp)
			return;
		comp.CloseSaveDialog();
	}
	void OnCloseClicked() {
		TMFR_EditorUIManagerComponent comp = TMFR_EditorUIManagerComponent.GetInstance();
		if(!comp)
			return;
		comp.CloseSaveDialog();
	}
}