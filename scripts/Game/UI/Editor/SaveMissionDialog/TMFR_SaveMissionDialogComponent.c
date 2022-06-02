class TMFR_SaveMissionDialogComponent : MenuRootSubComponent {
	EditBoxWidget missionNameEditBox;
	EditBoxWidget missionFileNameEditBox;
	[Attribute("BackButton")]
	protected string m_sCloseButton;
	
	[Attribute("SaveButton")]
	protected string m_sSaveMissionButton;
	protected static TMFR_SaveMissionDialogComponent m_Instance;
	static TMFR_SaveMissionDialogComponent GetInstance() {
		return m_Instance;
	}
	void TMFR_SaveMissionDialogComponent() {
		m_Instance = this;
		
	}
	override void HandlerAttached(Widget w) {
		super.HandlerAttached(w);
		missionNameEditBox = EditBoxWidget.Cast(w.FindAnyWidget("MissionNameEditBox"));
		missionFileNameEditBox = EditBoxWidget.Cast(w.FindAnyWidget("MissionFileNameEditBox"));
		
		Widget buttonWidget = w.FindAnyWidget(m_sCloseButton);
		if (buttonWidget)
			ButtonActionComponent.GetOnAction(buttonWidget).Insert(OnCloseClicked);
		
		buttonWidget = w.FindAnyWidget(m_sSaveMissionButton);
		if (buttonWidget)
			ButtonActionComponent.GetOnAction(buttonWidget).Insert(OnSaveClicked);
	}
	void OnSaveClicked(Widget widget, float value, EActionTrigger actionTrigger) {
		TMFR_UIManagerComponent comp = TMFR_UIManagerComponent.GetInstance();
		if(!comp)
			return;
		comp.Save(missionNameEditBox.GetText(), missionFileNameEditBox.GetText());
		comp.CloseSaveDialog();
	}
	void OnCloseClicked(Widget widget, float value, EActionTrigger actionTrigger) {
		TMFR_UIManagerComponent comp = TMFR_UIManagerComponent.GetInstance();
		if(!comp)
			return;
		comp.CloseSaveDialog();
	}
}