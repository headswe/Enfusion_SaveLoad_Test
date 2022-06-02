class TMFR_GameModeEditorClass: SCR_BaseGameModeClass
{
};

class TMFR_GameModeEditor : SCR_BaseGameMode
{
	[Attribute(defvalue: "1", category: "Game Mode: Editor")]
	protected bool m_bAutoInitEditor;
	
	[Attribute(defvalue: SCR_Enum.GetDefault(EGameModeEditorTarget.VOTE), category: "Game Mode: Editor", desc: "Who will become the Game Master?", uiwidget: UIWidgets.ComboBox, enums: ParamEnumArray.FromEnum(EGameModeEditorTarget))]
	protected EGameModeEditorTarget m_GameMasterTarget;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--- Variables
	protected int m_iPersistentGameMasterPlayerID;
	protected SCR_EditorManagerCore m_Core;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--- Public getters, anywhere
	/*!
	Get game master target which dictates how players obtain their GM rights. Note that target might be forced to change on evaluate on server if set on voting is enabled and the player is hosting
	Main use is to check if target == EVERYBODY or NOBODY
	\return EGameModeEditorTarget enum holding the information regarding the target type
	*/
	EGameModeEditorTarget GetGameMasterTarget()
	{
		return m_GameMasterTarget;
	}
	
	protected void OnEditorManagerCreatedServer(SCR_EditorManagerEntity editorManager)
	{
		if (editorManager.GetPlayerID() == SCR_PlayerController.GetLocalPlayerId() || m_GameMasterTarget == EGameModeEditorTarget.EVERYBODY)
		{
			SCR_VotingManagerComponent votingManager = SCR_VotingManagerComponent.GetInstance();
			if (votingManager)
			{
				votingManager.StartVoting(EVotingType.EDITOR_IN, editorManager.GetPlayerID());
				votingManager.EndVoting(EVotingType.EDITOR_IN, editorManager.GetPlayerID(), EVotingOutcome.FORCE_WIN);
			}
			return;
		}
	}
	protected void OnEditorManagerDeletedServer(SCR_EditorManagerEntity editorManager)
	{
	}
	protected void OnEditorManagerInitOwner(SCR_EditorManagerEntity editorManager)
	{		
		if (editorManager.IsLimited())
		{
			//--- ToDo: Show after spawn?
			SCR_HintSequenceComponent hintSequence = SCR_HintSequenceComponent.Cast(FindComponent(SCR_HintSequenceComponent));
			if (hintSequence)
				GetGame().GetCallqueue().CallLater(hintSequence.StartSequence, 1000); //--- ToDo: Don't hardcode the delay?
		}
		//Open editor if the game has not ended
		else if (GetState() != SCR_EGameModeState.POSTGAME)
		{			
			editorManager.SetAutoInit(m_bAutoInitEditor);
		}
	}
	
	//Limited changed, so call notification and show hint
	protected void OnLimitedChanged(bool isLimited)
	{
		SCR_EditorManagerEntity editorManager = SCR_EditorManagerEntity.GetInstance();
		if (!editorManager) return;
		
		int playerID = editorManager.GetPlayerID();
		
		//Became Player
		if (isLimited)
		{
			SCR_NotificationsComponent.SendToEveryone(ENotification.EDITOR_PLAYER_NO_LONGER_GM, playerID);
		}
		//Became GM
		else 
		{
			SCR_NotificationsComponent.SendToEveryone(ENotification.EDITOR_PLAYER_BECAME_GM, playerID);
		}
	}
	protected void OnPlayerTerminated(int playerId)
	{
		//--- When solo, open the editor after death
		if (m_Core.GetEditorManager(playerId) == SCR_EditorManagerEntity.GetInstance() && GetGame().GetPlayerManager().GetPlayerCount() == 1)
		{
			SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
			if (!playerController || !playerController.IsPossessing())
				SCR_EditorManagerEntity.OpenInstance();
		}
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--- Override functions
	protected override void OnPlayerDisconnected(int playerId)
	{
		//~ Hot fix. EditorManager of disconnected player is deleted before SCR_NotificationSenderComponent can catch it thus it never knows if the player that left was a GM
		if (IsMaster())
		{
			SCR_EditorManagerEntity editorManager;
		
			SCR_EditorManagerCore core = SCR_EditorManagerCore.Cast(SCR_EditorManagerCore.GetInstance(SCR_EditorManagerCore));
			if (core)
			{
				 editorManager = core.GetEditorManager(playerId);
			}
	
			//Leave Notification GM
			if (editorManager && !editorManager.IsLimited())
				SCR_NotificationsComponent.SendToEveryone(ENotification.EDITOR_GM_LEFT, playerId);
			//Leave notification Player
			else
				SCR_NotificationsComponent.SendToEveryone(ENotification.PLAYER_LEFT, playerId);
		}
		
		super.OnPlayerDisconnected(playerId);
	}
	
	override void OnPlayerKilled(int playerId, IEntity player, IEntity killer)
	{
		OnPlayerTerminated(playerId);
		super.OnPlayerKilled(playerId, player, killer);
	}
	override void OnPlayerDeleted(int playerId, IEntity player)
	{
		OnPlayerTerminated(playerId);
		super.OnPlayerDeleted(playerId, player);
	}
	override void OnGameStart()
	{
		super.OnGameStart();
		
		if (RplSession.Mode() == RplMode.Client || !m_Core)
			return;
		
		m_Core.Event_OnEditorManagerCreatedServer.Insert(OnEditorManagerCreatedServer);
		m_Core.Event_OnEditorManagerDeletedServer.Insert(OnEditorManagerDeletedServer);
		
		SCR_EditorManagerEntity localEditorManager = SCR_EditorManagerEntity.GetInstance();
		if (localEditorManager)
			OnEditorManagerCreatedServer(localEditorManager);
	}
	void TMFR_GameModeEditor(IEntitySource src, IEntity parent)
	{
		m_Core = SCR_EditorManagerCore.Cast(SCR_EditorManagerCore.GetInstance(SCR_EditorManagerCore));
		if (!m_Core) return;

		m_Core.Event_OnEditorManagerInitOwner.Insert(OnEditorManagerInitOwner);
	}
	void ~TMFR_GameModeEditor()
	{
		SCR_EditorManagerEntity editorManager = SCR_EditorManagerEntity.GetInstance();
		if (editorManager)
			editorManager.GetOnLimitedChange().Remove(OnLimitedChanged);
	}
};