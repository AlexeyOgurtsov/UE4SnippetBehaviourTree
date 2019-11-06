// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BehaviourTreeQuickEditor_NoPrecompTarget : BehaviourTreeQuickEditorTarget 
{
	public BehaviourTreeQuickEditor_NoPrecompTarget(TargetInfo Target) : base(Target)
	{
		bUseUnityBuild = false;
		bUsePCHFiles = false;
	}
}
