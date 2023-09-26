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
	float4 Position : SV_POSITION; // �ʒu���W�ł�.
	float4 Color    : COLOR;       // ���_�J���[�ł�.
};

//
// PSOutput
//
struct PSOutput
{
	float4 Color : SV_TARGET0; // �s�N�Z���J���[�ł�
};

//
// �s�N�Z���V�F�[�_�̃��C���G���g���[�|�C���g�ł�
//
PSOutput main(VSOutput input)
{
	PSOutput output = (PSOutput)0;

	output.Color = input.Color;

	return output;
}