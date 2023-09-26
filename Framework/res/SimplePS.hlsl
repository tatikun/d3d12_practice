//
//
//
//
//

//
// VSOutput structure
//
struct VSOutput
{
	float4 Position : SV_POSITION; // 位置座標です.
	float4 Color    : COLOR;       // 頂点カラーです.
};

//
// PSOutput
//
struct PSOutput
{
	float4 Color : SV_TARGET0; // ピクセルカラーです
};

//
// ピクセルシェーダのメインエントリーポイントです
//
PSOutput main(VSOutput input)
{
	PSOutput output = (PSOutput)0;

	output.Color = input.Color;

	return output;
}