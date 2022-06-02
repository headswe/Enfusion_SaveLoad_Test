class TMFR_ModeInfoBarMissionEditorUIComponent: ScriptedWidgetComponent
{
	[Attribute("OpenPauseMenuButton")]
	protected string m_sPauseMenuButtonName;
	
	[Attribute("CloseEditorButton")]
	protected string m_sCloseEditorButtonName;
	
	[Attribute("OpenSaveMenuButton")]
	protected string m_sOpenSaveMissionEditorButtonName;
	
	[Attribute("OpenLoadMenuButton")]
	protected string m_sOpenLoadMissionEditorButtonName;
	
	protected void OpenPauseMenuButton(Widget widget, float value, EActionTrigger actionTrigger)
	{
		if (!GetGame().GetMenuManager().IsAnyDialogOpen())
			ArmaReforgerScripted.OpenPauseMenu();
	}
	
	protected void CloseEditorButton(Widget widget, float value, EActionTrigger actionTrigger)
	{
		SCR_EditorManagerEntity editorManagerEntity = SCR_EditorManagerEntity.GetInstance();
		
		if (editorManagerEntity)
			editorManagerEntity.Close();
	}
	
	protected void OpenSaveDialogButton(Widget widget, float value, EActionTrigger actionTrigger) {
		TMFR_UIManagerComponent comp = TMFR_UIManagerComponent.GetInstance();
		if(!comp)
			return;
		comp.OpenSaveDialog();
	}
	protected void OpenLoadDialogButton(Widget widget, float value, EActionTrigger actionTrigger) {
		TMFR_UIManagerComponent comp = TMFR_UIManagerComponent.GetInstance();
		if(!comp)
			return;
		comp.OpenLoadDialog();
	}
	
	override void HandlerAttached(Widget w)
	{
		Widget buttonWidget = w.FindAnyWidget(m_sPauseMenuButtonName);
		if (buttonWidget)
			ButtonActionComponent.GetOnAction(buttonWidget).Insert(OpenPauseMenuButton);
		
		buttonWidget = w.FindAnyWidget(m_sCloseEditorButtonName);
		if (buttonWidget)
			ButtonActionComponent.GetOnAction(buttonWidget).Insert(CloseEditorButton);
		
		buttonWidget = w.FindAnyWidget(m_sOpenSaveMissionEditorButtonName);
		if (buttonWidget)
			ButtonActionComponent.GetOnAction(buttonWidget).Insert(OpenSaveDialogButton);
		
		buttonWidget = w.FindAnyWidget(m_sOpenLoadMissionEditorButtonName);
		if (buttonWidget)
			ButtonActionComponent.GetOnAction(buttonWidget).Insert(OpenLoadDialogButton);
	}
	
};
