[BaseContainerProps(), SCR_BaseContainerCustomTitleUIInfo("m_Info")]
class TMFR_LoadToolbarAction : SCR_BaseToggleToolbarAction
{
	override bool IsServer()
	{
		return true;
	}
	
	override bool CanBeShown(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags)
	{
		return true;
	}
	override bool CanBePerformed(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags)
	{
		return true;
	}
	
	override void Perform(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition,int flags, int param = -1)
	{		
		TMFR_EditorUIManagerComponent comp = TMFR_EditorUIManagerComponent.GetInstance();
		if(!comp)
			return;
		comp.OpenLoadDialog();
	}
	
	override void Track()
	{

	}
	

	override void Untrack()
	{

	}
};
	
