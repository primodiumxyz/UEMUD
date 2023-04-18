
#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcClient.h"
#include "EventSystem/Message/CF_Message.h"
#include "SEcssnapshot/EcsSnapshotMessage.h"
#include "UObject/Object.h"
#include "SEcsstream/EcsStreamService.h"
#include "TurboLinkGrpc/Public/TurboLinkGrpcClient.h"
#include "M_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FGrpcContextHandle Handle = FGrpcContextHandle();

	UPROPERTY(BlueprintReadOnly)
	FGrpcResult Result;

	UPROPERTY(BlueprintReadOnly)
	FGrpcEcssnapshotECSStateReply Response;

	


	FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse(
		FGrpcContextHandle _Handle,
		const FGrpcResult& _Result,
		const FGrpcEcssnapshotECSStateReply& _Response)
	{
		Handle = _Handle;
		Result = _Result;
		Response = _Response;
		
	}
	
	FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse()
	{
		Handle = FGrpcContextHandle();
		Result = FGrpcResult();
		Response = FGrpcEcssnapshotECSStateReply();
	}

	
};
