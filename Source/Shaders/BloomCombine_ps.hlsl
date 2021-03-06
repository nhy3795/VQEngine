//	DX11Renderer - VDemo | DirectX11 Renderer
//	Copyright(C) 2016  - Volkan Ilbeyli
//
//	This program is free software : you can redistribute it and / or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.If not, see <http://www.gnu.org/licenses/>.
//
//	Contact: volkanilbeyli@gmail.com

#define DO_BLOOM

struct PSIn
{
	float4 position : SV_POSITION;
	float2 uv		: TEXCOORD0;
};

Texture2D ColorTexture;
Texture2D BloomTexture;
SamplerState BlurSampler;

float4 PSMain(PSIn In) : SV_TARGET
{
	float3 outColor;
	const float3 color = ColorTexture.Sample(BlurSampler, In.uv);
	const float3 bloom = BloomTexture.Sample(BlurSampler, In.uv);
	
#ifdef DO_BLOOM
	if (length(bloom) != 0.0f)
		outColor = color + bloom;
	else
		outColor = color;
#else
	outColor = color;
#endif
	return float4(outColor, 1);
}