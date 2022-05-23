[ComponentEditorProps(category: "GameScripted/Editor", description: "", icon: "WBData/ComponentEditorProps/componentEditor.png")]
class TMFR_EditorUIManagerComponentClass: SCR_BaseEditorComponentClass
{
};

/** @ingroup Editor_Components
Manager of unique editor states
*/
class TMFR_EditorUIManagerComponent : ScriptComponent
{
	Widget m_LoadDialog;
	Widget m_SaveDialog;
	ResourceName loadDialogLayout = "{313CE55773C7A138}UI/layouts/Editor/MissionList/LoadMissionDialog.layout";
	ResourceName saveDialogLayout = "{5A4229D1E23B06A7}UI/layouts/Editor/SaveMissionDialog/TMFR_SaveMissionDialog.layout";
	protected static TMFR_EditorUIManagerComponent m_Instance;
	static TMFR_EditorUIManagerComponent GetInstance()
	{
		return m_Instance;
	}
	void TMFR_EditorUIManagerComponent() {
		m_Instance = this;
	}
	override void OnPostInit(IEntity owner) {

	}
	private Widget CreateDialog(ResourceName res) {
		Widget p = GetGame().GetMenuManager().GetTopMenu().GetRootWidget();
		Widget w = GetGame().GetWorkspace().CreateWidgets(res, p);
		
		FrameSlot.SetAnchorMin(w, 0, 0);
		FrameSlot.SetAnchorMax(w, 1, 1);
		FrameSlot.SetOffsets(w, 0, 0, 0, 0);
		w.Update();
		return w;
	}
	private void CloseDialog(Widget widget) {
		if(!widget)
		  return;
		widget.GetParent().RemoveChild(widget);
		widget = null;
	}
	void OpenLoadDialog() {
		m_LoadDialog = CreateDialog(loadDialogLayout);
	}
	void CloseLoadDialog() {
		CloseDialog(m_LoadDialog);
		m_LoadDialog = null;
	}
	void OpenSaveDialog() {
		m_SaveDialog = CreateDialog(saveDialogLayout);
	}
	void CloseSaveDialog() {
		CloseDialog(m_SaveDialog);
		m_SaveDialog = null;
	}
};