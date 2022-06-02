[BaseContainerProps()]
class TMFR_MissionStruct: SCR_JsonApiStruct
{
	[Attribute()]
	protected ref TMFR_EditorStruct m_EditorStruct;
	
	
	override bool Serialize()
	{
		if (m_EditorStruct && !m_EditorStruct.Serialize())
			return false;
	
		return true;
	}
	override bool Deserialize()
	{
		if (m_EditorStruct && !m_EditorStruct.Deserialize())
			return false;
	
		return true;
	}
	override void Log()
	{
		if (m_EditorStruct)
			m_EditorStruct.Log();
	}
	void TMFR_MissionStruct()
	{
		RegV("m_EditorStruct");
	}
};