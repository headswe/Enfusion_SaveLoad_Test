[BaseContainerProps(), SCR_BaseContainerCustomTitleUIInfo("m_Info")]
class TMFR_SaveToolbarAction : SCR_BaseToggleToolbarAction
{
	override bool IsServer()
	{
		return false;
	}
	
	override bool CanBeShown(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags)
	{
		return true;
	}
	override bool CanBePerformed(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags)
	{
		return true;
	}
	
	override void PerformOwner(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags, int param = -1)
	{
		TMFR_UIManagerComponent comp = TMFR_UIManagerComponent.GetInstance();
		if(!comp)
			return;
		comp.OpenSaveDialog();
	}
	override void Track()
	{

	}
	

	override void Untrack()
	{

	}
};
	
