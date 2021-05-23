#include <stdio.h>
#include <string>
struct AptCharacter;
struct AptFloatArrayCXForm
{
    float scale[4];
    float translate[4];
};
struct AptMatrix
{
    float a;
    float b;
    float c;
    float d;
    float tx;
    float ty;
};
struct AptRect
{
    float fLeft;
    float fTop;
    float fRight;
    float fBottom;
};
struct AptCharacterGlyphEntry
{
    short nIndex;
    short nAdvance;
};
struct AptCharacterStaticTextRecords
{
    int nFontID;
    AptFloatArrayCXForm cxform;
    float fXOffset;
    float fYOffset;
    float fScale;
    int nGlyphs;
    AptCharacterGlyphEntry* aGlyphs;
};
struct AptCharacterStaticText
{
    AptRect rBounds;
    AptMatrix matrix;
    int nFontRecords;
    AptCharacterStaticTextRecords* aRecords;
};
struct AptNativeHash;
enum AptControlType {
    AptControlType_DoAction = 1,
    AptControlType_FrameLabel,
    AptControlType_PlaceObject2,
    AptControlType_RemoveObject2,
    AptControlType_BackgroundColour,
    AptControlType_StartSound,
    AptControlType_StartSoundStream,
    AptControlType_DoInitAction
};
struct AptControlBackgroundColour
{
    unsigned int nColour;
};
struct AptControlSound
{
    int nID;
};
struct AptControlRemoveObject2
{
    int nDepth;
};
enum AptPlaceObjectFlags {
    AptPlaceObjectFlag_None = 0,
    AptPlaceObjectFlag_Move = 1,
    AptPlaceObjectFlag_Character = 2,
    AptPlaceObjectFlag_Matrix = 4,
    AptPlaceObjectFlag_CXForm = 8,
    AptPlaceObjectFlag_Ratio = 16,
    AptPlaceObjectFlag_Name = 32,
    AptPlaceObjectFlag_DefineClip = 64,
    AptPlaceObjectFlag_Actions = 128
};
struct AptUint32CXForm
{
    unsigned int nScale;
    unsigned int nBias;
};
struct AptActionBlock
{
    char* aActionStream;
};
struct AptEventActionBlock
{
    int nTriggers;
    int nKeyCode;
    AptActionBlock actions;
};
struct AptEventActionSet
{
    int nEventActions;
    AptEventActionBlock* aEventActions;
};
struct AptControlPlaceObject2
{
    AptPlaceObjectFlags eFlags;
    int nDepth;
    int nCharacterID;
    AptMatrix matrix;
    AptUint32CXForm ncxform;
    float fRatio;
    char* szName;
    int nClipDepth;
    AptEventActionSet* pActions;
};
struct AptControlFrameLabel
{
    char* szLabel;
};
struct AptControlDoInitAction
{
    int nSpriteID;
    AptActionBlock actions;
};
struct AptControlDoAction
{
    AptActionBlock actions;
};
struct AptControl
{
    AptControlType eType;
    union
    {
        AptControlDoAction action;
        AptControlDoInitAction initAction;
        AptControlFrameLabel frameLabel;
        AptControlPlaceObject2 placeObject2;
        AptControlRemoveObject2 removeObject2;
        AptControlBackgroundColour backgroundColour;
        AptControlSound startSound;
        AptControlSound startSoundStream;
    };
};
struct AptFrame
{
    int nControls;
    AptControl** apControls;
};
struct AptMovie
{
    int nFrames;
    AptFrame* aFrames;
    AptNativeHash* phLabels;
};
struct AptCharacterSprite
{
    AptMovie movie;
};
struct AptFile;
struct AptImport
{
    char* szFile;
    char* szName;
    int nID;
    AptFile *file;
};
struct AptExport
{
    char* szName;
    int nID;
};
struct AptCharacterAnimation : AptCharacterSprite
{
    int nCharacters;
    AptCharacter** apCharacters;
    unsigned int nWidth;
    unsigned int nHeight;
    unsigned int nMillisecondsPerFrame;
    int nImports;
    AptImport* aImports;
    int nExports;
    AptExport* aExports;
    int nCurrentConstantIndex;
};
struct AptCharacterBitmap
{
    void* zID;
};
struct AptCharacterSound
{
    void* zID;
};
enum AptCharacterButtonRecordState
{
    AptCharacterButtonRecordState_None,
    AptCharacterButtonRecordState_Up,
    AptCharacterButtonRecordState_Over,
    AptCharacterButtonRecordState_Down,
    AptCharacterButtonRecordState_HitTest,
};
struct AptCharacterButtonRecord
{
    AptCharacterButtonRecordState eStates;
    AptCharacter* pCharacter;
    int nLayer;
    AptMatrix matrix;
    AptFloatArrayCXForm cxform;
};
enum AptActionConditionFlag
{
    AptActionConditionFlag_IdleToOverUp = 0x1,
    AptActionConditionFlag_OverUpToIdle = 0x2,
    AptActionConditionFlag_OverUpToOverDown = 0x4,
    AptActionConditionFlag_OverDownToOverUp = 0x8,
    AptActionConditionFlag_OverDownToOutDown = 0x10,
    AptActionConditionFlag_OutDownToOverDown = 0x20,
    AptActionConditionFlag_OutDownToIdle = 0x40,
    AptActionConditionFlag_IdleToOverDown = 0x80,
    AptActionConditionFlag_OverDownToIdle = 0x100,
    AptActionConditionFlag_KeyPress = 0xFE00,
};
struct AptActionConditionBlock
{
    int nConditions;
    AptActionBlock actions;
};
struct AptCharacterButtonSound
{
    AptCharacter* pOverUpToIdle;
    AptCharacter* pIdleToOverUp;
    AptCharacter* pOverUpToOverDown;
    AptCharacter* pOverDownToOverUp;
};
struct AptCharacterButton
{
    int bIsMenu;
    AptRect mHitTestBoundingRect;
    int mHitTestTriangles;
    int mHitTestVertexCount;
    float* mHitTestVertexTable;
    short* mHitTestIndexTable;
    int nButtonRecords;
    AptCharacterButtonRecord* aButtonRecords;
    int nActionConditions;
    AptActionConditionBlock* aActionConditions;
    AptCharacterButtonSound* pButtonSound;
};
struct AptCharacterFont
{
    char* szName;
    int nGlyphs;
    AptCharacter** apGlyphs;
};
enum AptStringAlignment
{
    AptStringAlignment_Left,
    AptStringAlignment_Right,
    AptStringAlignment_Center,
    AptStringAlignment_None,
    AptStringAlignment_Justify,
};
struct AptCharacterText
{
    AptRect rBounds;
    int nFontID;
    AptStringAlignment eAlignment;
    unsigned int nColour;
    float fFontHeight;
    int bReadOnly;
    int bMultiLine;
    int bWordWrap;
    char* szInitialText;
    char* szVariable;
};
struct AptCharacterShape
{
    AptRect rBounds;
    void* zID;
};
struct AptCharacterMorph
{
    AptCharacter* pStartCharacter;
    AptCharacter* pEndCharacter;
};
enum AptCharacterType
{
    AptCharacterType_Shape = 1,
    AptCharacterType_Text,
    AptCharacterType_Font,
    AptCharacterType_Button,
    AptCharacterType_Sprite,
    AptCharacterType_Sound,
    AptCharacterType_Bitmap,
    AptCharacterType_Morph,
    AptCharacterType_Animation,
    AptCharacterType_StaticText,
    AptCharacterType_None,
    AptCharacterType_Video,
    AptCharacterType_Level = 15,
    AptCharacterType_CustomControl,
    AptCharacterType_Max,
};
struct AptCharacter
{
    AptCharacterType eType;
    AptCharacter* pParentAnim;
    union
    {
        AptCharacterShape shape;
        AptCharacterMorph morph;
        AptCharacterText text;
        AptCharacterFont font;
        AptCharacterButton button;
        AptCharacterSprite sprite;
        AptCharacterSound sound;
        AptCharacterBitmap bitmap;
        AptCharacterAnimation animation;
        AptCharacterStaticText statictext;
    };
};

enum AptVirtualFunctionTable_Indices
{
    AptVFT_xxx,
    AptVFT_StringValue,
    AptVFT_Property,
    AptVFT_None,
    AptVFT_Register,
    AptVFT_Boolean,
    AptVFT_Float,
    AptVFT_Integer,
    AptVFT_Lookup,
    AptVFT_NativeFunction,
    AptVFT_FrameStack,
    AptVFT_Extern,
    AptVFT_CharacterInstHandle,
    AptVFT_Sound,
    AptVFT_Array,
    AptVFT_Math,
    AptVFT_Key,
    AptVFT_Global,
    AptVFT_ScriptColour,
    AptVFT_Object,
    AptVFT_Prototype,
    AptVFT_Date,
    AptVFT_MovieClip,
    AptVFT_Mouse,
    AptVFT_XmlNode,
    AptVFT_Xml,
    AptVFT_XmlAttributes,
    AptVFT_LoadVars,
    AptVFT_TextFormat,
    AptVFT_Extension,
    AptVFT_GlobalExtension,
    AptVFT_Stage,
    AptVFT_Error,
    AptVFT_StringObject,
    AptVFT_ScriptFunction1,
    AptVFT_ScriptFunction2,
    AptVFT_ScriptFunctionByteCodeBlock,
    AptVFT_CIHNone,
    AptVFT_NumVFTs,
};
struct AptConstantTable
{
    AptVirtualFunctionTable_Indices eType;
    union
    {
        char* szString;
        float fFloat;
        int nInteger;
        int nRegister;
        int bBoolean;
        unsigned int nLookup;
    };
};
struct AptConstFile
{
	char aMagic[20];
	AptCharacter* pMainCharacter;
	int nConstants;
	AptConstantTable *aConstants;
};

enum Actions {
    AptActionInvalid = -1,
    AptActionEnd = 0,
    AptActionNextFrame = 4,
    AptActionPrevFrame = 5,
    AptActionPlay = 6,
    AptActionStop = 7,
    AptActionToggleQuality = 8,
    AptActionStopSounds = 9,
    AptActionAdd = 10,
    AptActionSubtract = 11,
    AptActionMultiply = 12,
    AptActionDivide = 13,
    AptActionEquals = 14,
    AptActionLessThan = 15,
    AptActionAnd = 16,
    AptActionOr = 17,
    AptActionNot = 18,
    AptActionStringEquals = 19,
    AptActionStringLength = 20,
    AptActionSubString = 21,
    AptActionPop = 23,
    AptActionToInteger = 24,
    AptActionGetVariable = 28,
    AptActionSetVariable = 29,
    AptActionSetTarget2 = 32,
    AptActionStringAdd = 33,
    AptActionGetProperty = 34,
    AptActionSetProperty = 35,
    AptActionCloneSprite = 36,
    AptActionRemoveSprite = 37,
    AptActionTrace = 38,
    AptActionStartDragMovie = 39,
    AptActionStopDragMovie = 40,
    AptActionStringLessThan = 41,
    AptActionThrow = 42,
    AptActionCastOp = 43,
    AptActionImplementsOp = 44,
    AptActionRandom = 48,
    AptActionMBLength = 49,
    AptActionCharToAscii = 50,
    AptActionAsciiToChar = 51,
    AptActionGetTimer = 52,
    AptActionMBSubString = 53,
    AptActionMBCharToAscii = 54,
    AptActionMBAsciiToChar = 55,
    AptActionDelete = 58,
    AptActionDelete2 = 59,
    AptActionDefineLocal = 60,
    AptActionCallFunction = 61,
    AptActionReturn = 62,
    AptActionModulo = 63,
    AptActionNewObject = 64,
    AptActionDefineLocal2 = 65,
    AptActionInitArray = 66,
    AptActionInitObject = 67,
    AptActionTypeOf = 68,
    AptActionTargetPath = 69,
    AptActionEnumerate = 70,
    AptActionAdd2 = 71,
    AptActionLessThan2 = 72,
    AptActionEquals2 = 73,
    AptActionToNumber = 74,
    AptActionToString = 75,
    AptActionPushDuplicate = 76,
    AptActionStackSwap = 77,
    AptActionGetMember = 78,
    AptActionSetMember = 79,
    AptActionIncrement = 80,
    AptActionDecrement = 81,
    AptActionCallMethod = 82,
    AptActionNewMethod = 83,
    AptActionInstanceOf = 84,
    AptActionEnumerate2 = 85,
    AptActionPushThis = 86,
    AptActionPushGlobal = 88,
    AptActionPush0 = 89,
    AptActionPush1 = 90,
    AptActionCallFuncAndPop = 91,
    AptActionCallFuncSetVar = 92,
    AptActionCallMethodPop = 93,
    AptActionCallMethodSetVar = 94,
    AptActionBitAnd = 96,
    AptActionBitOr = 97,
    AptActionBitXor = 98,
    AptActionBitLShift = 99,
    AptActionBitRShift = 100,
    AptActionBitURShift = 101,
    AptActionStrictEquals = 102,
    AptActionGreater = 103,
    AptActionExtends = 105,
    AptActionPushThisVariable = 112,
    AptActionPushGlobalVariable = 113,
    AptActionPushZeroSetVar = 114,
    AptActionPushTrue = 115,
    AptActionPushFalse = 116,
    AptActionPushNULL = 117,
    AptActionPushUndefined = 118,
    AptActionTraceStart = 119,
    AptActionGotoFrame = 129,
    AptActionGetUrl = 131,
    AptActionStoreRegister = 135,
    AptActionDefineDictionary = 136,
    AptActionWaitForFrame = 138,
    AptActionSetTarget = 139,
    AptActionGotoLabel = 140,
    AptActionDefineFunction2 = 142,
    AptActionTry = 143,
    AptActionWith = 148,
    AptActionPush = 150,
    AptActionBranchAlways = 153,
    AptActionGetUrl2 = 154,
    AptActionDefineFunction = 155,
    AptActionBranchIfTrue = 157,
    AptActionCallFrame = 158,
    AptActionGotoFrame2 = 159,
    AptActionPushString = 161,
    AptActionPushStringDictByte = 162,
    AptActionPushStringDictWord = 163,
    AptActionPushStringGetVar = 164,
    AptActionPushStringGetMember = 165,
    AptActionPushStringSetVar = 166,
    AptActionPushStringSetMember = 167,
    AptActionStringDictByteGetVar = 174,
    AptActionStringDictByteGetMember = 175,
    AptActionDictCallFuncPop = 176,
    AptActionDictCallFuncSetVar = 177,
    AptActionDictCallMethodPop = 178,
    AptActionDictCallMethodSetVar = 179,
    AptActionPushFloat = 180,
    AptActionPushByte = 181,
    AptActionPushWord = 182,
    AptActionPushDWord = 183,
    AptActionBranchIfFalse = 184,
    AptActionPushRegister = 185,
    LastAptAction = 186,
};

const char* actionstrings[LastAptAction] = {
"&end", //0
"", //1
"", //2
"", //3
"&nextFrame", //4
"&prevFrame", //5
"&play", //6
"&stop", //7
"&toggleQuality", //8
"&stopSounds", //9
"&addOld", //10
"&subtract", //11
"&multiply", //12
"&divide", //13
"&equalsOld", //14
"&lessThanOld", //15
"&and", //16
"&or", //17
"&not", //18
"&stringEq", //19
"&stringLen", //20
"&subStr", //21
"", //22
"&pop", //23
"&int", //24
"", //25
"", //26
"", //27
"&getVariable", //28
"&setVariable", //29
"", //30
"", //31
"&setTarget", //32
"&concat", //33
"&getProperty", //34
"&setProperty", //35
"&cloneSprite", //36
"&removeClip", //37
"&trace", //38
"&startDragMovie", //39
"&stopDragMovie", //40
"&stringLT", //41
"&throw", //42
"&cast", //43
"&implements", //44
"", //45
"", //46
"", //47
"&random", //48
"&mbLength", //49
"&charToAscii", //50
"&asciiToChar", //51
"&getTimer", //52
"&mbSubString", //53
"&mbCharToAscii", //54
"&mbAsciiToChar", //55
"", //56
"", //57
"&delete", //58
"&delete2", //59
"&varEquals", //60
"&callFunction", //61
"&return", //62
"&modulo", //63
"&new", //64
"&var", //65
"&initArray", //66
"&initObject", //67
"&typeof", //68
"&targetPathOld", //69
"&enumerateOld", //70
"&add", //71
"&lessThan", //72
"&equals", //73
"&toNumber", //74
"&toString", //75
"&dup", //76
"&swap", //77
"&getMember", //78
"&setMember", //79
"&increment", //80
"&decrement", //81
"&callMethod", //82
"&newMethod", //83
"&instanceOf", //84
"&enumerate", //85
"&pushthis", //86
"", //87
"&pushglobal", //88
"&pushzero", //89
"&pushone", //90
"&callfp", //91
"&callfsv", //92
"&callmp", //93
"&callmsv", //94
"", //95
"&bitwiseAnd", //96
"&bitwiseOr", //97
"&bitwiseXor", //98
"&shiftLeft", //99
"&shiftRight", //100
"&shiftRightUnsigned", //101
"&strictEquals", //102
"&greaterThan", //103
"", //104
"&extends", //105
"", //106
"", //107
"", //108
"", //109
"", //110
"", //111
"&pushthisgv", //112
"&pushglobalgv", //113
"&pushzerosv", //114
"&pushtrue", //115
"&pushfalse", //116
"&pushnull", //117
"&pushundef", //118
"&traceStart", //119
"", //120
"", //121
"", //122
"", //123
"", //124
"", //125
"", //126
"", //127
"", //128
"&gotoFrame", //129
"", //130
"&getURL", //131
"", //132
"", //133
"", //134
"&setRegister", //135
"&constants", //136
"", //137
"&waitForFrame", //138
"&setTarget", //139
"&gotoLabel", //140
"", //141
"&function2", //142
"&try", //143
"", //144
"", //145
"", //146
"", //147
"&with", //148
"", //149
"&push", //150
"", //151
"", //152
"&jmp", //153
"&getURL2", //154
"&function", //155
"", //156
"&jnz", //157
"&callFrame", //158
"&gotoAndPlay", //159
"", //160
"&pushs", //161
"&pushsdb", //162
"&pushsdw", //163
"&pushsgv", //164
"&pushsgm", //165
"&pushssv", //166
"&pushssm", //167
"", //168
"", //169
"", //170
"", //171
"", //172
"", //173
"&pushsdbgv", //174
"&pushsdbgm", //175
"&dcallfp", //176
"&dcallfsv", //177
"&dcallmp", //178
"&dcallmsv", //179
"&pushfloat", //180
"&pushbyte", //181
"&pushshort", //182
"&pushlong", //183
"&jz", //184
"&pushregister" //185
};

struct AptValue;
struct AptConstantPool
{
    int nItems;
    AptValue** apItems;
};

struct AptAction_BranchAddress
{
    int nTargetDelta;
};
struct AptAction_DefineFunction
{
    const char* szName;
    int nParams;
    char** aszParams;
    int nCodeSize;
    AptConstantPool constantPool;
};
struct AptRegisterParam
{
    unsigned int nRegister;
    char* szParamName;
};
struct AptAction_DefineFunction2
{
    const char* szName;
    int nParams;
    short nRegisterCount;
    short nFlags;
    AptRegisterParam* aszParams;
    int nCodeSize;
    AptConstantPool constantPool;
};
struct AptAction_GetUrl
{
    char* szUrl;
    char* szWin;
};
struct AptAction_GotoFrame
{
    int nFrame;
};
struct AptAction_GotoFrame2
{
    int bPlay;
};
struct AptAction_GotoLabel
{
    char* szLabel;
};
struct AptAction_Push
{
    AptConstantPool items;
};
struct AptAction_PushString
{
    char* szStringToBePushed;
};
struct AptAction_SetTarget
{
    char* szTarget;
};
struct AptAction_StoreRegister
{
    int nRegister;
};

enum AptTryCatchBlockFlagsType
{
    TCFB_HasCatchBlock = 1,
    TCFB_HasFinallyBlock = 2,
    TCFB_PutCaughtObjectInRegister = 4,
};

struct AptAction_TryCatchFinallyBlock
{
    unsigned int uTryCodeSize;
    unsigned int uCatchCodeSize;
    unsigned int uFinallyCodeSize;
    char uFlags;
    char uAlignment1;
    char uAlignment2;
    char uCaughtRegister;
    char* szCaughtVarName;
};
struct AptAction_With
{
    char* pEnd;
};

struct AptAptFile
{
    char aMagic[16];
};

template <typename T> void AddPointer(T*& ptr, unsigned char* base)
{
    if (ptr)
    {
        int& ptr2 = (int&)ptr;
        ptr2 += (int)base;
    }
}

void ParseActionStream(char* stream, unsigned char* aptdata, unsigned char* constdata)
{
    int opcode = (unsigned char)*stream;
    unsigned int pos = (unsigned int)(stream + 1);
    if (!*stream)
    {
        return;
    }
    for (;;)
    {
        switch (opcode)
        {
        case AptActionTraceStart:
        case AptActionPushFloat:
        case AptActionPushDWord:
            pos += 4;
            break;
        case AptActionGotoFrame:
        case AptActionStoreRegister:
        case AptActionBranchAlways:
        case AptActionBranchIfTrue:
        case AptActionGotoFrame2:
        case AptActionBranchIfFalse:
            pos = (pos + 3) & ~3;
            pos += 4;
            break;
        case AptActionGetUrl:
            {
                AptAction_GetUrl* url = (AptAction_GetUrl*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_GetUrl);
                AddPointer(url->szUrl, aptdata);
                AddPointer(url->szWin, aptdata);
            }
            break;
        case AptActionDefineDictionary:
        case AptActionPush:
            {
                AptAction_Push* push = (AptAction_Push*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_Push);
                AddPointer(push->items.apItems, aptdata);
            }
            break;
        case AptActionSetTarget:
            {
                AptAction_SetTarget* target = (AptAction_SetTarget*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_SetTarget);
                AddPointer(target->szTarget, aptdata);
            }
            break;
        case AptActionGotoLabel:
            {
                AptAction_GotoLabel* label = (AptAction_GotoLabel*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_GotoLabel);
                AddPointer(label->szLabel, aptdata);
            }
            break;
        case AptActionPushString:
        case AptActionPushStringGetVar:
        case AptActionPushStringGetMember:
        case AptActionPushStringSetVar:
        case AptActionPushStringSetMember:
            {
                AptAction_PushString* string = (AptAction_PushString*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_PushString);
                AddPointer(string->szStringToBePushed, aptdata);
            }
            break;
        case AptActionDefineFunction2:
            {
                AptAction_DefineFunction2* func = (AptAction_DefineFunction2*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_DefineFunction2);
                AddPointer(func->szName, aptdata);
                AddPointer(func->aszParams, aptdata);
                for (int i = 0; i < func->nParams; i++)
                {
                    AddPointer(func->aszParams[i].szParamName, aptdata);
                }
            }
            break;
        case AptActionTry:
            {
                AptAction_TryCatchFinallyBlock* block = (AptAction_TryCatchFinallyBlock*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_TryCatchFinallyBlock);
                if ((block->uFlags & TCFB_PutCaughtObjectInRegister) != 0)
                {
                    break;
                }
                AddPointer(block->szCaughtVarName, aptdata);
            }
            break;
        case AptActionWith:
            {
                AptAction_With* with = (AptAction_With*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_With);
                with->pEnd += pos;
            }
            break;
        case AptActionDefineFunction:
            {
                AptAction_DefineFunction* func = (AptAction_DefineFunction*)((pos + 3) & ~3);
                pos = ((pos + 3) & ~3) + sizeof(AptAction_DefineFunction);
                AddPointer(func->szName, aptdata);
                AddPointer(func->aszParams, aptdata);
                for (int i = 0; i < func->nParams; i++)
                {
                    AddPointer(func->aszParams[i], aptdata);
                }
            }
            break;
        case AptActionPushStringDictByte:
        case AptActionStringDictByteGetVar:
        case AptActionStringDictByteGetMember:
        case AptActionDictCallFuncPop:
        case AptActionDictCallFuncSetVar:
        case AptActionDictCallMethodPop:
        case AptActionDictCallMethodSetVar:
        case AptActionPushByte:
        case AptActionPushRegister:
            pos++;
            break;
        case AptActionPushStringDictWord:
        case AptActionPushWord:
            pos += 2;
            break;
        default:
            break;
        }
        opcode = *(unsigned char*)(pos++);
        if (!opcode)
        {
            break;
        }
    }
}

void ResolveMovie(AptMovie* movie, unsigned char* aptdata, unsigned char* constdata)
{
    AddPointer(movie->aFrames, aptdata);
    for (int i = 0; i < movie->nFrames; i++)
    {
        AptFrame* f = &movie->aFrames[i];
        AddPointer(f->apControls, aptdata);
        for (int j = 0; j < f->nControls; j++)
        {
            AddPointer(f->apControls[j], aptdata);
            switch (f->apControls[j]->eType)
            {
            case AptControlType_DoAction:
                AddPointer(f->apControls[j]->action.actions.aActionStream, aptdata);
                ParseActionStream(f->apControls[j]->action.actions.aActionStream, aptdata, constdata);
                break;
            case AptControlType_FrameLabel:
                AddPointer(f->apControls[j]->frameLabel.szLabel, aptdata);
                break;
            case AptControlType_PlaceObject2:
                AddPointer(f->apControls[j]->placeObject2.szName, aptdata);
                AddPointer(f->apControls[j]->placeObject2.pActions, aptdata);
                if (f->apControls[j]->placeObject2.pActions)
                {
                    AddPointer(f->apControls[j]->placeObject2.pActions->aEventActions, aptdata);
                    for (int k = 0; k < f->apControls[j]->placeObject2.pActions->nEventActions; k++)
                    {
                        AddPointer(f->apControls[j]->placeObject2.pActions->aEventActions[k].actions.aActionStream, aptdata);
                        ParseActionStream(f->apControls[j]->placeObject2.pActions->aEventActions[k].actions.aActionStream, aptdata, constdata);
                    }
                }
                break;
            case AptControlType_DoInitAction:
                AddPointer(f->apControls[j]->initAction.actions.aActionStream, aptdata);
                ParseActionStream(f->apControls[j]->initAction.actions.aActionStream, aptdata, constdata);
                break;
            default:
                break;
            }
        }
    }
}

void InitAnimation(AptCharacterAnimation* character, unsigned char* aptdata, unsigned char *constdata)
{
    AddPointer(character->apCharacters, aptdata);
    AddPointer(character->aExports, aptdata);
    for (int i = 0; i < character->nExports; i++)
    {
        AddPointer(character->aExports[i].szName, aptdata);
    }
    for (int i = 0; i < character->nCharacters; i++)
    {
        AddPointer(character->apCharacters[i], aptdata);
        if (character->apCharacters[i])
        {
            AptCharacter* c = character->apCharacters[i];
            c->pParentAnim = character->apCharacters[0];
            switch (c->eType)
            {
            case AptCharacterType_Shape:
                break;
            case AptCharacterType_Text:
                AddPointer(c->text.szInitialText, aptdata);
                AddPointer(c->text.szVariable, aptdata);
                break;
            case AptCharacterType_Font:
                AddPointer(c->font.szName, aptdata);
                AddPointer(c->font.apGlyphs, aptdata);
                break;
            case AptCharacterType_Button:
                AddPointer(c->button.mHitTestVertexTable, aptdata);
                AddPointer(c->button.mHitTestIndexTable, aptdata);
                AddPointer(c->button.aButtonRecords, aptdata);
                AddPointer(c->button.aActionConditions, aptdata);
                for (int j = 0; j < c->button.nActionConditions; j++)
                {
                    AddPointer(c->button.aActionConditions[j].actions.aActionStream, aptdata);
                    ParseActionStream(c->button.aActionConditions[j].actions.aActionStream, aptdata, constdata);
                }
                AddPointer(c->button.pButtonSound, aptdata);
                break;
            case AptCharacterType_Sprite:
            case AptCharacterType_Animation:
                ResolveMovie(&c->sprite.movie, aptdata, constdata);
                break;
            case AptCharacterType_Sound:
                break;
            case AptCharacterType_Bitmap:
                break;
            case AptCharacterType_StaticText:
                AddPointer(c->statictext.aRecords, aptdata);
                for (int j = 0; j < c->statictext.nFontRecords; j++)
                {
                    AddPointer(c->statictext.aRecords[j].aGlyphs, aptdata);
                }
                break;
            default:
                break;
            }
        }
    }
    AddPointer(character->aImports, aptdata);
    for (int i = 0; i < character->nImports; i++)
    {
        AddPointer(character->aImports[i].szFile, aptdata);
        AddPointer(character->aImports[i].szName, aptdata);
    }
}

void ProcessActions(FILE *f3, char* stream, unsigned char* aptdata, const char* indent)
{
    int opcode = (unsigned char)*stream;
    unsigned int pos = (unsigned int)(stream + 1);
    if (!*stream)
    {
        return;
    }
    for (;;)
    {
        switch (opcode)
        {
        case AptActionPushFloat:
            fprintf(f3, "%s%s %f\n", indent, actionstrings[opcode], *(float*)pos);
            pos += 4;
            break;
        case AptActionTraceStart:
        case AptActionPushDWord:
            fprintf(f3, "%s%s %d\n", indent, actionstrings[opcode], *(unsigned int*)pos);
            pos += 4;
            break;
        case AptActionGotoFrame:
        case AptActionStoreRegister:
        case AptActionBranchAlways:
        case AptActionBranchIfTrue:
        case AptActionGotoFrame2:
        case AptActionBranchIfFalse:
            pos = (pos + 3) & ~3;
            fprintf(f3, "%s%s %d\n", indent, actionstrings[opcode], *(unsigned int*)pos);
            pos += 4;
            break;
        case AptActionGetUrl:
        {
            AptAction_GetUrl* url = (AptAction_GetUrl*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_GetUrl);
            fprintf(f3, "%s%s %s %s\n", indent, actionstrings[opcode], url->szUrl, url->szWin);
        }
        break;
        case AptActionDefineDictionary:
        case AptActionPush:
        {
            AptAction_Push* push = (AptAction_Push*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_Push);
            fprintf(f3, "%s%s ", indent, actionstrings[opcode]);
            for (int i = 0; i < push->items.nItems; i++)
            {
                fprintf(f3, "%d", (int)push->items.apItems[i]);
                if (i < push->items.nItems - 1)
                {
                    fprintf(f3, " ");
                }
            }
            fprintf(f3, "\n");
        }
        break;
        case AptActionSetTarget:
        {
            AptAction_SetTarget* target = (AptAction_SetTarget*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_SetTarget);
            fprintf(f3, "%s%s %s\n", indent, actionstrings[opcode], target->szTarget);
        }
        break;
        case AptActionGotoLabel:
        {
            AptAction_GotoLabel* label = (AptAction_GotoLabel*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_GotoLabel);
            fprintf(f3, "%s%s %s\n", indent, actionstrings[opcode], label->szLabel);
        }
        break;
        case AptActionPushString:
        case AptActionPushStringGetVar:
        case AptActionPushStringGetMember:
        case AptActionPushStringSetVar:
        case AptActionPushStringSetMember:
        {
            AptAction_PushString* string = (AptAction_PushString*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_PushString);
            fprintf(f3, "%s%s %s\n", indent, actionstrings[opcode], string->szStringToBePushed);
        }
        break;
        case AptActionDefineFunction2:
        {
            AptAction_DefineFunction2* func = (AptAction_DefineFunction2*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_DefineFunction2);
            fprintf(f3, "%s%s %s 0x%08x (", indent, actionstrings[opcode], func->szName, func->nFlags);
            for (int i = 0; i < func->nParams; i++)
            {
                fprintf(f3, "%d = %s", func->aszParams[i].nRegister, func->aszParams[i].szParamName);
                if (i < func->nParams - 1)
                {
                    fprintf(f3, ",");
                }
            }
            fprintf(f3, ")\n");
        }
        break;
        case AptActionTry:
        {
            AptAction_TryCatchFinallyBlock* block = (AptAction_TryCatchFinallyBlock*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_TryCatchFinallyBlock);
            if ((block->uFlags & TCFB_PutCaughtObjectInRegister) != 0)
            {
                fprintf(f3, "%s%s %d %d %d %d %d %d %d\n", indent, actionstrings[opcode], block->uTryCodeSize, block->uCatchCodeSize, block->uFinallyCodeSize, block->uFlags, block->uAlignment1, block->uAlignment2, block->uCaughtRegister);
                break;
            }
            fprintf(f3, "%s%s %d %d %d %d %d %d %s\n", indent, actionstrings[opcode], block->uTryCodeSize, block->uCatchCodeSize, block->uFinallyCodeSize, block->uFlags, block->uAlignment1, block->uAlignment2, block->szCaughtVarName);
        }
        break;
        case AptActionWith:
        {
            AptAction_With* with = (AptAction_With*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_With);
            fprintf(f3, "%s%s %d\n", indent, actionstrings[opcode], (int)with->pEnd);
            with->pEnd += pos;
        }
        break;
        case AptActionDefineFunction:
        {
            AptAction_DefineFunction* func = (AptAction_DefineFunction*)((pos + 3) & ~3);
            pos = ((pos + 3) & ~3) + sizeof(AptAction_DefineFunction);
            fprintf(f3, "%s%s %s 0x%08x (", indent, actionstrings[opcode], func->szName, func->nParams);
            for (int i = 0; i < func->nParams; i++)
            {
                fprintf(f3, "%s", func->aszParams[i]);
                if (i < func->nParams - 1)
                {
                    fprintf(f3, ",");
                }
            }
            fprintf(f3, ")\n");
        }
        break;
        case AptActionPushStringDictByte:
        case AptActionStringDictByteGetVar:
        case AptActionStringDictByteGetMember:
        case AptActionDictCallFuncPop:
        case AptActionDictCallFuncSetVar:
        case AptActionDictCallMethodPop:
        case AptActionDictCallMethodSetVar:
        case AptActionPushByte:
        case AptActionPushRegister:
            fprintf(f3, "%s%s %d\n", indent, actionstrings[opcode], *(unsigned char*)pos);
            pos++;
            break;
        case AptActionPushStringDictWord:
        case AptActionPushWord:
            fprintf(f3, "%s%s %d\n", indent, actionstrings[opcode], *(unsigned short*)pos);
            pos += 2;
            break;
        default:
            fprintf(f3, "%s%s\n", indent, actionstrings[opcode]);
            break;
        }
        opcode = *(unsigned char*)(pos++);
        if (!opcode)
        {
            break;
        }
    }
}

void ParseApt(const char* name)
{
    FILE* f;
    std::string str = name;
    str += ".apt";
    fopen_s(&f, str.c_str(), "rb");
    FILE* f2;
    std::string str2 = name;
    str2 += ".const";
    fopen_s(&f2, str2.c_str(), "rb");
    fseek(f, 0, SEEK_END);
    int aptsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char* aptdata = new unsigned char[aptsize];
    unsigned char* aptpos = aptdata;
    fread(aptdata, 1, aptsize, f);
    fseek(f2, 0, SEEK_END);
    int constsize = ftell(f2);
    fseek(f2, 0, SEEK_SET);
    unsigned char* constdata = new unsigned char[constsize];
    unsigned char* constpos = constdata;
    fread(constdata, 1, constsize, f2);
    fclose(f);
    fclose(f2);
    AptConstFile* c = (AptConstFile*)constdata;
    AddPointer(c->pMainCharacter, aptdata);
    AddPointer(c->aConstants, constdata);
    for (int i = 0; i < c->nConstants; i++)
    {
        switch (c->aConstants[i].eType)
        {
        case AptVFT_StringValue:
            AddPointer(c->aConstants[i].szString, constdata);
            break;
        default:
            break;
        }
    }
    InitAnimation(&c->pMainCharacter->animation, aptdata, constdata);
    std::string str3 = name;
    str3 += ".txt";
    FILE* f3;
    fopen_s(&f3, str3.c_str(), "wt");
    if (!f3)
    {
        return;
    }
    for (int i = 0; i < c->nConstants; i++)
    {
        switch (c->aConstants[i].eType)
        {
        case AptVFT_StringValue:
            fprintf(f3, "String Constant %s\n", c->aConstants[i].szString);
            break;
        default:
            fprintf(f3, "Unknown Constant Type %d\n", c->aConstants[i].eType);
            break;
        }
    }
    AptCharacterAnimation *m = &c->pMainCharacter->animation;
    fprintf(f3, "Movie Clip:\n");
    fprintf(f3, "Screen Size %d %d\n", m->nWidth, m->nHeight);
    fprintf(f3, "Milliseconds Per Frame %d\n", m->nMillisecondsPerFrame);
    fprintf(f3, "Imports:\n");
    for (int i = 0; i < m->nImports; i++)
    {
        fprintf(f3, "\tCharacter %s imported from movie %s at position %d\n", m->aImports[i].szName, m->aImports[i].szFile, m->aImports[i].nID);
    }
    fprintf(f3, "Exports:\n");
    for (int i = 0; i < m->nExports; i++)
    {
        fprintf(f3, "\tCharacter %d exported as %s\n", m->aExports[i].nID, m->aExports[i].szName);
    }
    for (int i = 0; i < m->movie.nFrames; i++)
    {
        fprintf(f3, "Frame %d:\n", i);
        for (int j = 0; j < m->movie.aFrames[i].nControls; j++)
        {
            switch (m->movie.aFrames[i].apControls[j]->eType)
            {
            case AptControlType_DoAction:
            {
                AptControlDoAction* oa = &m->movie.aFrames[i].apControls[j]->action;
                fprintf(f3, "\tAction:\n");
                ProcessActions(f3, oa->actions.aActionStream, aptdata, "\t\t");
            }
            break;
            case AptControlType_FrameLabel:
            {
                AptControlFrameLabel* fl = &m->movie.aFrames[i].apControls[j]->frameLabel;
                fprintf(f3, "\tFrame Label:\n");
                fprintf(f3, "\tLabel \"%s\"\n", fl->szLabel);
            }
            break;
            case AptControlType_PlaceObject2:
            {
                AptControlPlaceObject2* po = &m->movie.aFrames[i].apControls[j]->placeObject2;
                fprintf(f3, "\tPlace Object:\n");
                fprintf(f3, "\tFlags %d\n", po->eFlags);
                fprintf(f3, "\tDepth %d\n", po->nClipDepth);
                fprintf(f3, "\tCharacter %d\n", po->nCharacterID);
                fprintf(f3, "\tRotate/Scale %f %f %f %f\n", po->matrix.a, po->matrix.b, po->matrix.c, po->matrix.d);
                fprintf(f3, "\tTranslate %f %f\n", po->matrix.tx, po->matrix.ty);
                fprintf(f3, "\tColor Transform %d %d\n", po->ncxform.nBias, po->ncxform.nScale);
                fprintf(f3, "\tRatio %f\n", po->fRatio);
                if (po->szName)
                {
                    fprintf(f3, "\tName \"%s\"\n", po->szName);
                }
                fprintf(f3, "\tClip Depth %d\n", po->nClipDepth);
                if (po->pActions)
                {
                    fprintf(f3, "\tClip Actions:\n");
                    for (int k = 0; k < po->pActions->nEventActions; k++)
                    {
                        fprintf(f3, "\tKey Code 0x%08x\n", po->pActions->aEventActions[k].nKeyCode);
                        fprintf(f3, "\tTriggers 0x%08x\n", po->pActions->aEventActions[k].nTriggers);
                        ProcessActions(f3, po->pActions->aEventActions[k].actions.aActionStream, aptdata, "\t\t");
                    }
                }
            }
            break;
            case AptControlType_RemoveObject2:
            {
                AptControlRemoveObject2* ro = &m->movie.aFrames[i].apControls[j]->removeObject2;
                fprintf(f3, "\tRemove Object:\n");
                fprintf(f3, "\tDepth %d\n", ro->nDepth);
            }
            break;
            case AptControlType_BackgroundColour:
            {
                AptControlBackgroundColour* bg = &m->movie.aFrames[i].apControls[j]->backgroundColour;
                fprintf(f3, "\tBackground Color:\n");
                fprintf(f3, "\tColor 0x%08x\n", bg->nColour);
            }
            break;
            case AptControlType_DoInitAction:
            {
                AptControlDoInitAction* oa = &m->movie.aFrames[i].apControls[j]->initAction;
                fprintf(f3, "\tInitAction for sprite %d:\n", oa->nSpriteID);
                ProcessActions(f3, oa->actions.aActionStream, aptdata, "\t\t");
            }
            break;
            }
        }
    }
    for (int ch = 0; ch < m->nCharacters; ch++)
    {
        fprintf(f3, "Character %d:\n", ch);
        if (!m->apCharacters[ch])
        {
            continue;
        }
        switch (m->apCharacters[ch]->eType)
        {
        case AptCharacterType_Shape:
        {
            AptCharacterShape* sh = &m->apCharacters[ch]->shape;
            fprintf(f3, "Shape:\n");
            fprintf(f3, "Bounds %f %f %f %f\n", sh->rBounds.fTop, sh->rBounds.fLeft, sh->rBounds.fBottom, sh->rBounds.fRight);
        }
        break;
        case AptCharacterType_Text:
        {
            AptCharacterText* et = &m->apCharacters[ch]->text;
            fprintf(f3, "EditText:\n");
            fprintf(f3, "Bounds %f %f %f %f\n", et->rBounds.fTop, et->rBounds.fLeft, et->rBounds.fBottom, et->rBounds.fRight);
            fprintf(f3, "Font %d\n", et->nFontID);
            fprintf(f3, "Alignment %d\n", et->eAlignment);
            fprintf(f3, "Color 0x%08x\n", et->nColour);
            fprintf(f3, "Font Height %f\n", et->fFontHeight);
            fprintf(f3, "Read Only %d\n", et->bReadOnly);
            fprintf(f3, "Multiline %d\n", et->bMultiLine);
            fprintf(f3, "Word Wrap %d\n", et->bWordWrap);
            if (et->szInitialText)
            {
                fprintf(f3, "Text %s\n", et->szInitialText);
            }
            if (et->szVariable)
            {
                fprintf(f3, "Variable %s\n", et->szVariable);
            }
        }
        break;
        case AptCharacterType_Font:
        {
            AptCharacterFont* fo = &m->apCharacters[ch]->font;
            fprintf(f3, "Font:\n");
            fprintf(f3, "Name %s\n", fo->szName);
            if (fo->nGlyphs)
            {
                fprintf(f3, "Glyphs ");
                for (int i = 0; i < fo->nGlyphs; i++)
                {
                    fprintf(f3, "%d", (int)fo->apGlyphs[i]);
                    if (i < fo->nGlyphs - 1)
                    {
                        fprintf(f3, ",");
                    }
                }
                fprintf(f3, "\n");
            }
        }
        break;
        case AptCharacterType_Button:
        {
            AptCharacterButton* ob = &m->apCharacters[ch]->button;
            fprintf(f3, "Button:\n");
            fprintf(f3, "Is Menu %d\n", ob->bIsMenu);
            if (ob->pButtonSound)
            {
                fprintf(f3, "Button Sound %d %d %d %d\n", (int)ob->pButtonSound->pIdleToOverUp, (int)ob->pButtonSound->pOverDownToOverUp, (int)ob->pButtonSound->pOverUpToIdle, (int)ob->pButtonSound->pOverUpToOverDown);
            }
            fprintf(f3, "Bounds %f %f %f %f\n", ob->mHitTestBoundingRect.fTop, ob->mHitTestBoundingRect.fLeft, ob->mHitTestBoundingRect.fBottom, ob->mHitTestBoundingRect.fRight);
            if (ob->mHitTestTriangles)
            {
                fprintf(f3, "Triangles:\n");
                for (int i = 0; i < ob->mHitTestTriangles; i++)
                {
                    fprintf(f3, "\tTriangle %d v1 %f %f v2 %f %f v3 %f %f\n", i, ob->mHitTestVertexTable[ob->mHitTestIndexTable[i * 3] * 2], ob->mHitTestVertexTable[ob->mHitTestIndexTable[i * 3] * 2 + 1], ob->mHitTestVertexTable[ob->mHitTestIndexTable[i * 3 + 1] * 2], ob->mHitTestVertexTable[ob->mHitTestIndexTable[i * 3 + 1] * 2 + 1], ob->mHitTestVertexTable[ob->mHitTestIndexTable[i * 3 + 2] * 2], ob->mHitTestVertexTable[ob->mHitTestIndexTable[i * 3 + 2] * 2 + 1]);
                }
            }
            if (ob->nButtonRecords)
            {
                for (int i = 0; i < ob->nButtonRecords; i++)
                {
                    fprintf(f3, "Record %d:\n", i);
                    fprintf(f3, "\tStates 0x%08x\n", ob->aButtonRecords[i].eStates);
                    fprintf(f3, "\tCharacter %d\n", (int)ob->aButtonRecords[i].pCharacter);
                    fprintf(f3, "\tLayer %d\n", ob->aButtonRecords[i].nLayer);
                    fprintf(f3, "\tRotate/Scale %f %f %f %f\n", ob->aButtonRecords[i].matrix.a, ob->aButtonRecords[i].matrix.b, ob->aButtonRecords[i].matrix.c, ob->aButtonRecords[i].matrix.d);
                    fprintf(f3, "\tTranslate %f %f\n", ob->aButtonRecords[i].matrix.tx, ob->aButtonRecords[i].matrix.ty);
                    fprintf(f3, "\tCXForm Scale %f %f %f %f\n", ob->aButtonRecords[i].cxform.scale[0], ob->aButtonRecords[i].cxform.scale[1], ob->aButtonRecords[i].cxform.scale[2], ob->aButtonRecords[i].cxform.scale[3]);
                    fprintf(f3, "\tCXForm Translate %f %f %f %f\n", ob->aButtonRecords[i].cxform.translate[0], ob->aButtonRecords[i].cxform.translate[1], ob->aButtonRecords[i].cxform.translate[2], ob->aButtonRecords[i].cxform.translate[3]);
                }
            }
            if (ob->nActionConditions)
            {
                for (int i = 0; i < ob->nActionConditions; i++)
                {
                    fprintf(f3, "Button Action Record %d:\n", i);
                    fprintf(f3, "\tConditions 0x%08x\n", ob->aActionConditions[i].nConditions);
                    ProcessActions(f3, ob->aActionConditions[i].actions.aActionStream, aptdata, "\t");
                }
            }
        }
        break;
        case AptCharacterType_Sprite:
        {
            AptCharacterSprite* sp = &m->apCharacters[ch]->sprite;
            fprintf(f3, "Sprite:\n");
            for (int i = 0; i < sp->movie.nFrames; i++)
            {
                fprintf(f3, "Frame %d:\n", i);
                for (int j = 0; j < sp->movie.aFrames[i].nControls; j++)
                {
                    switch (sp->movie.aFrames[i].apControls[j]->eType)
                    {
                    case AptControlType_DoAction:
                    {
                        AptControlDoAction* oa = &sp->movie.aFrames[i].apControls[j]->action;
                        fprintf(f3, "\tAction:\n");
                        ProcessActions(f3, oa->actions.aActionStream, aptdata, "\t\t");
                    }
                    break;
                    case AptControlType_FrameLabel:
                    {
                        AptControlFrameLabel* fl = &sp->movie.aFrames[i].apControls[j]->frameLabel;
                        fprintf(f3, "\tFrame Label:\n");
                        fprintf(f3, "\tLabel \"%s\"\n", fl->szLabel);
                    }
                    break;
                    case AptControlType_PlaceObject2:
                    {
                        AptControlPlaceObject2* po = &sp->movie.aFrames[i].apControls[j]->placeObject2;
                        fprintf(f3, "\tPlace Object:\n");
                        fprintf(f3, "\tFlags %d\n", po->eFlags);
                        fprintf(f3, "\tDepth %d\n", po->nClipDepth);
                        fprintf(f3, "\tCharacter %d\n", po->nCharacterID);
                        fprintf(f3, "\tRotate/Scale %f %f %f %f\n", po->matrix.a, po->matrix.b, po->matrix.c, po->matrix.d);
                        fprintf(f3, "\tTranslate %f %f\n", po->matrix.tx, po->matrix.ty);
                        fprintf(f3, "\tColor Transform %d %d\n", po->ncxform.nBias, po->ncxform.nScale);
                        fprintf(f3, "\tRatio %f\n", po->fRatio);
                        if (po->szName)
                        {
                            fprintf(f3, "\tName \"%s\"\n", po->szName);
                        }
                        fprintf(f3, "\tClip Depth %d\n", po->nClipDepth);
                        if (po->pActions)
                        {
                            fprintf(f3, "\tClip Actions:\n");
                            for (int k = 0; k < po->pActions->nEventActions; k++)
                            {
                                fprintf(f3, "\tKey Code 0x%08x\n", po->pActions->aEventActions[k].nKeyCode);
                                fprintf(f3, "\tTriggers 0x%08x\n", po->pActions->aEventActions[k].nTriggers);
                                ProcessActions(f3, po->pActions->aEventActions[k].actions.aActionStream, aptdata, "\t\t");
                            }
                        }
                    }
                    break;
                    case AptControlType_RemoveObject2:
                    {
                        AptControlRemoveObject2* ro = &sp->movie.aFrames[i].apControls[j]->removeObject2;
                        fprintf(f3, "\tRemove Object:\n");
                        fprintf(f3, "\tDepth %d\n", ro->nDepth);
                    }
                    break;
                    case AptControlType_BackgroundColour:
                    {
                        AptControlBackgroundColour* bg = &sp->movie.aFrames[i].apControls[j]->backgroundColour;
                        fprintf(f3, "\tBackground Color:\n");
                        fprintf(f3, "\tColor 0x%08x\n", bg->nColour);
                    }
                    break;
                    case AptControlType_DoInitAction:
                    {
                        AptControlDoInitAction* oa = &sp->movie.aFrames[i].apControls[j]->initAction;
                        fprintf(f3, "\tInitAction for sprite %d:\n", oa->nSpriteID);
                        ProcessActions(f3, oa->actions.aActionStream, aptdata, "\t\t");
                    }
                    break;
                    }
                }
            }
        }
        break;
        case AptCharacterType_Bitmap:
        {
            AptCharacterBitmap* im = &m->apCharacters[ch]->bitmap;
            fprintf(f3, "Image:\n");
            fprintf(f3, "Id %d\n", (int)im->zID);
        }
        break;
        case AptCharacterType_Morph:
        {
            AptCharacterMorph* mo = &m->apCharacters[ch]->morph;
            fprintf(f3, "Morph:\n");
            fprintf(f3, "Start Character: %d\n", (int)mo->pStartCharacter);
            fprintf(f3, "End Character: %d\n", (int)mo->pEndCharacter);
        }
        break;
        case AptCharacterType_StaticText:
        {
            AptCharacterStaticText* te = &m->apCharacters[ch]->statictext;
            fprintf(f3, "Text:\n");
            fprintf(f3, "Bounds %f %f %f %f\n", te->rBounds.fTop, te->rBounds.fLeft, te->rBounds.fBottom, te->rBounds.fRight);
            fprintf(f3, "\tRotate/Scale %f %f %f %f\n", te->matrix.a, te->matrix.b, te->matrix.c, te->matrix.d);
            fprintf(f3, "\tTranslate %f %f\n", te->matrix.tx, te->matrix.ty);
            if (te->nFontRecords)
            {
                for (int i = 0; i < te->nFontRecords; i++)
                {
                    fprintf(f3, "Record %d:\n", i);
                    fprintf(f3, "\tFont %d\n", te->aRecords[i].nFontID);
                    fprintf(f3, "\tCXForm Scale %f %f %f %f\n", te->aRecords[i].cxform.scale[0], te->aRecords[i].cxform.scale[1], te->aRecords[i].cxform.scale[2], te->aRecords[i].cxform.scale[3]);
                    fprintf(f3, "\tCXForm Translate %f %f %f %f\n", te->aRecords[i].cxform.translate[0], te->aRecords[i].cxform.translate[1], te->aRecords[i].cxform.translate[2], te->aRecords[i].cxform.translate[3]);
                    fprintf(f3, "\tOffset %f %f\n", te->aRecords[i].fXOffset, te->aRecords[i].fYOffset);
                    fprintf(f3, "\tScale %f\n", te->aRecords[i].fScale);
                    if (te->aRecords[i].nGlyphs)
                    {
                        fprintf(f3, "\tGlyphs:\n");
                        for (int j = 0; j < te->aRecords[i].nGlyphs; j++)
                        {
                            fprintf(f3, "\tIndex %d Advance %d\n", te->aRecords[i].aGlyphs[j].nIndex, te->aRecords[i].aGlyphs[j].nAdvance);
                        }
                    }
                }
            }
        }
        break;
        }
    }
    fclose(f3);
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        ParseApt(argv[1]);
    }
}
