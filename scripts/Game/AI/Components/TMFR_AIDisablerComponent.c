[ComponentEditorProps(category: "GameScripted/AI", description: "Component for utility AI system calculations", color: "0 0 255 255")]
class TMFR_AIDisablerComponentClass: ScriptComponentClass
{
};

//------------------------------------------------------------------------------------------------
class TMFR_AIDisablerComponent : ScriptComponent
{
	[Attribute( defvalue: "1", uiwidget: UIWidgets.CheckBox, desc: "Disable AI on spawn" )]
	bool m_DisableAI;
	protected SCR_AIWorld m_AIWorld;
	
	override void OnPostInit(IEntity owner) {
		m_AIWorld = SCR_AIWorld.Cast(owner);
		if(m_AIWorld == null)
		  return;
		m_AIWorld.s_OnAgentSpawned.Insert(AddedAIAgent);
	}
	void AddedAIAgent(AIAgent agent) {
		SCR_AIGroup grp = SCR_AIGroup.Cast(agent);
		if(grp)
			return;
		IEntity soldier = agent.GetControlledEntity();
		if(!soldier) {
			Print("No soldier?");
			return;
		}
		AIControlComponent controlComponent = AIControlComponent.Cast(soldier.FindComponent(AIControlComponent));
		if(!controlComponent) {
			Print("No controlComponent?");
			return;
		}
		controlComponent.DeactivateAI();
		
	}
};