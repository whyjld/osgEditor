#include "QsciLexerGlsl.h"
#include <Qsci/qsciscintilla.h>
#include "glsllexer.h"

#include <iostream>
#include <sstream>
#include <vector>

QsciLexerGLSL::QsciLexerGLSL(QsciScintilla* parent)
    : QsciLexerCustom(parent)
    , m_Parent(parent)
    , m_API(new QsciAPIs(this))
    , m_FlexScanner(new yyFlexLexer())
{
    m_API->add("radians (genType degrees)");
    m_API->add("degrees (genType radians)");
    m_API->add("sin (genType angle)");
    m_API->add("cos (genType angle)");
    m_API->add("tan (genType angle)");
    m_API->add("sinh (genType x)");
    m_API->add("cosh (genType x)");
    m_API->add("tanh (genType x)");
    m_API->add("sqrt (genType x)");
    m_API->add("sqrt (genDType x)");
    m_API->add("inversesqrt (genType x)");
    m_API->add("inversesqrt (genDType x)");
    m_API->add("abs (genType x)");
    m_API->add("abs (genIType x)");
    m_API->add("abs (genDType x)");
    m_API->add("sign (genType x)");
    m_API->add("sign (genIType x)");
    m_API->add("sign (genDType x)");
    m_API->add("floor (genType x)");
    m_API->add("floor (genDType x)");
    m_API->add("trunc (genType x)");
    m_API->add("trunc (genDType x)");
    m_API->add("round (genType x)");
    m_API->add("round (genDType x)");
    m_API->add("roundEven (genType x)");
    m_API->add("roundEven (genDType x)");
    m_API->add("ceil (genType x)");
    m_API->add("ceil (genDType x)");
    m_API->add("fract (genType x)");
    m_API->add("fract (genDType x)");
    m_API->add("mod (genType x, float y)");
    m_API->add("mod (genType x, genType y)");
    m_API->add("mod (genDType x, double y)");
    m_API->add("mod (genDType x, genDType y)");
    m_API->add("modf (genType x, out genType i)");
    m_API->add("modf (genDType x, out genDType i)");
    m_API->add("min (genType x, genType y)");
    m_API->add("min (genType x, float y)");
    m_API->add("min (genDType x, genDType y)");
    m_API->add("min (genDType x, double y)");
    m_API->add("min (genIType x, genIType y)");
    m_API->add("min (genIType x, int y)");
    m_API->add("min (genUType x, genUType y)");
    m_API->add("min (genUType x, uint y)");
    m_API->add("max (genType x, genType y)");
    m_API->add("max (genType x, float y)");
    m_API->add("max (genDType x, genDType y)");
    m_API->add("max (genDType x, double y)");
    m_API->add("max (genIType x, genIType y)");
    m_API->add("max (genIType x, int y)");
    m_API->add("max (genUType x, genUType y)");
    m_API->add("max (genUType x, uint y)");
    m_API->add("clamp (genType x, genType minVal, genType maxVal)");
    m_API->add("clamp (genType x, float minVal, float maxVal)");
    m_API->add("clamp (genDType x, genDType minVal, genDType maxVal)");
    m_API->add("clamp (genDType x, double minVal, double maxVal)");
    m_API->add("clamp (genIType x, genIType minVal, genIType maxVal)");
    m_API->add("clamp (genIType x, int minVal, int maxVal)");
    m_API->add("clamp (genUType x, genUType minVal, genUType maxVal)");
    m_API->add("clamp (genUType x, uint minVal, uint maxVal)");
    m_API->add("min (max (x, minVal)");
    m_API->add("mix (genType x, genType y, genType a)");
    m_API->add("mix (genType x, genType y, float a)");
    m_API->add("mix (genDType x, genDType y, genDType a)");
    m_API->add("mix (genDType x, genDType y, double a)");
    m_API->add("mix (genType x, genType y, genBType a)");
    m_API->add("mix (genDType x, genDType y, genBType a)");
    m_API->add("mix (genIType x, genIType y, genBType a)");
    m_API->add("mix (genUType x, genUType y, genBType a)");
    m_API->add("mix (genBType x, genBType y, genBType a)");
    m_API->add("step (genType edge, genType x)");
    m_API->add("step (float edge, genType x)");
    m_API->add("step (genDType edge, genDType x)");
    m_API->add("step (double edge, genDType x)");
    m_API->add("smoothstep (genType edge0, genType edge1, genType x)");
    m_API->add("smoothstep (float edge0, float edge1, genType x)");
    m_API->add("smoothstep (genDType edge0, genDType edge1, genDType x)");
    m_API->add("smoothstep (double edge0, double edge1, genDType x)");
    m_API->add("isnan (genType x)");
    m_API->add("isnan (genDType x)");
    m_API->add("isinf (genType x)");
    m_API->add("isinf (genDType x)");
    m_API->add("floatBitsToInt (genType value)");
    m_API->add("floatBitsToUint (genType value)");
    m_API->add("intBitsToFloat (genIType value)");
    m_API->add("uintBitsToFloat (genUType value)");
    m_API->add("fma (genType a, genType b, genType c)");
    m_API->add("fma (genDType a, genDType b, genDType c)");
    m_API->add("frexp (genType x, out genIType exp)");
    m_API->add("frexp (genDType x, out genIType exp)");
    m_API->add("ldexp (genType x, in genIType exp)");
    m_API->add("ldexp (genDType x, in genIType exp)");
    m_API->add("packUnorm2x16 (vec2 v)");
    m_API->add("packSnorm2x16 (vec2 v)");
    m_API->add("packUnorm4x8 (vec4 v)");
    m_API->add("packSnorm4x8 (vec4 v)");
    m_API->add("unpackUnorm2x16 (uint p)");
    m_API->add("unpackSnorm2x16 (uint p)");
    m_API->add("unpackUnorm4x8 (uint p)");
    m_API->add("unpackSnorm4x8 (uint p)");
    m_API->add("unpackDouble2x32 (double v)");
    m_API->add("unpackHalf2x16 (uint v)");
    m_API->add("length (genType x)");
    m_API->add("length (genDType x)");
    m_API->add("distance (genType p0, genType p1)");
    m_API->add("distance (genDType p0,genDType p1)");
    m_API->add("dot (genType x, genType y)");
    m_API->add("dot (genDType x, genDType y)");
    m_API->add("cross (vec3 x, vec3 y)");
    m_API->add("cross (dvec3 x, dvec3 y)");
    m_API->add("normalize (genType x)");
    m_API->add("normalize (genDType x)");
    m_API->add("ftransform ()");
    m_API->add("faceforward (genType N,genType I,genType Nref)");
    m_API->add("faceforward (genDType N,genDType I,genDType Nref)");
    m_API->add("reflect (genType I, genType N)");
    m_API->add("reflect (genDType I,genDType N)");
    m_API->add("refract (genType I, genType N,float eta)");
    m_API->add("refract (genDType I,genDType N,float eta)");
    m_API->add("outerProduct (vec2 c, vec2 r)");
    m_API->add("outerProduct (vec3 c, vec3 r)");
    m_API->add("outerProduct (vec4 c, vec4 r)");
    m_API->add("outerProduct (vec3 c, vec2 r)");
    m_API->add("outerProduct (vec2 c, vec3 r)");
    m_API->add("outerProduct (vec4 c, vec2 r)");
    m_API->add("outerProduct (vec2 c, vec4 r)");
    m_API->add("outerProduct (vec4 c, vec3 r)");
    m_API->add("outerProduct (vec3 c, vec4 r)");
    m_API->add("transpose (mat2 m)");
    m_API->add("transpose (mat3 m)");
    m_API->add("transpose (mat4 m)");
    m_API->add("transpose (mat3x2 m)");
    m_API->add("transpose (mat2x3 m)");
    m_API->add("transpose (mat4x2 m)");
    m_API->add("transpose (mat2x4 m)");
    m_API->add("transpose (mat4x3 m)");
    m_API->add("transpose (mat3x4 m)");
    m_API->add("determinant (mat2 m)");
    m_API->add("determinant (mat3 m)");
    m_API->add("determinant (mat4 m)");
    m_API->add("inverse (mat2 m)");
    m_API->add("inverse (mat3 m)");
    m_API->add("inverse (mat4 m)");
    m_API->add("lessThan (vec x, vec y)");
    m_API->add("lessThan (ivec x, ivec y)");
    m_API->add("lessThan (uvec x, uvec y)");
    m_API->add("lessThanEqual (vec x, vec y)");
    m_API->add("lessThanEqual (ivec x, ivec y)");
    m_API->add("lessThanEqual (uvec x, uvec y)");
    m_API->add("greaterThan (vec x, vec y)");
    m_API->add("greaterThan (ivec x, ivec y)");
    m_API->add("greaterThan (uvec x, uvec y)");
    m_API->add("greaterThanEqual (vec x, vec y)");
    m_API->add("greaterThanEqual (ivec x, ivec y)");
    m_API->add("greaterThanEqual (uvec x, uvec y)");
    m_API->add("equal (vec x, vec y)");
    m_API->add("equal (ivec x, ivec y)");
    m_API->add("equal (uvec x, uvec y)");
    m_API->add("equal (bvec x, bvec y)");
    m_API->add("notEqual (vec x, vec y)");
    m_API->add("notEqual (ivec x, ivec y)");
    m_API->add("notEqual (uvec x, uvec y)");
    m_API->add("notEqual (bvec x, bvec y)");
    m_API->add("uaddCarry (genUType x,genUType y,out genUType carry)");
    m_API->add("usubBorrow (genUType x,genUType y,out genUTypeborrow)");
    m_API->add("umulExtended (genUType x,genUType y,out genUType msb,out genUType lsb)");
    m_API->add("imulExtended (genIType x,genIType y,out genIType msb,out genIType lsb)");
    m_API->add("bitfieldExtract (genIType value,int offset, int bits)");
    m_API->add("bitfieldExtract (genUType value,int offset, int bits)");
    m_API->add("bitfieldInsert (genIType base,genIType insert,int offset, int bits)");
    m_API->add("bitfieldInsert (genUType base,genUType insert,int offset, int bits)");
    m_API->add("bitfieldReverse (genIType value)");
    m_API->add("bitfieldReverse (genUType value)");
    m_API->add("bitCount (genIType value)");
    m_API->add("bitCount (genUType value)");
    m_API->add("findLSB (genIType value)");
    m_API->add("findLSB (genUType value)");
    m_API->add("findMSB (genIType value)");
    m_API->add("findMSB (genUType value)");
    m_API->add("if (computedLod < TEXTURE_MIN_LOD)");
    m_API->add("if (computedLod > TEXTURE_MAX_LOD)");
    m_API->add("if (computedLod < 0.0)");
    m_API->add("if (computedLod > (float)");
    m_API->add("if (TEXTURE_MIN_FILTER is LINEAR or NEAREST)");
    m_API->add("textureSize (gsampler2D sampler, int lod)");
    m_API->add("textureSize (gsampler3D sampler, int lod)");
    m_API->add("textureSize (gsamplerCube sampler, int lod)");
    m_API->add("textureSize (sampler2DShadow sampler, int lod)");
    m_API->add("textureSize (samplerCubeShadow sampler, int lod)");
    m_API->add("textureSize (gsamplerCubeArray sampler, int lod)");
    m_API->add("textureSize (samplerCubeArrayShadow sampler, int lod)");
    m_API->add("textureSize (gsampler2DRect sampler)");
    m_API->add("textureSize (sampler2DRectShadow sampler)");
    m_API->add("textureSize (gsampler1DArray sampler, int lod)");
    m_API->add("textureSize (gsampler2DArray sampler, int lod)");
    m_API->add("textureSize (sampler1DArrayShadow sampler, int lod)");
    m_API->add("textureSize (sampler2DArrayShadow sampler, int lod)");
    m_API->add("textureSize (gsampler2DMS sampler)");
    m_API->add("textureSize (gsampler2DMSArray sampler)");
    m_API->add("texture (gsampler1D sampler, float P [, float bias] )");
    m_API->add("texture (gsampler2D sampler, vec2 P [, float bias] )");
    m_API->add("texture (gsampler3D sampler, vec3 P [, float bias] )");
    m_API->add("texture (gsamplerCube sampler, vec3 P [, float bias] )");
    m_API->add("texture (gsampler1DArray sampler, vec2 P [, float bias] )");
    m_API->add("texture (gsampler2DArray sampler, vec3 P [, float bias] )");
    m_API->add("texture (gsamplerCubeArray sampler, vec4 P [, float bias] )");
    m_API->add("texture (gsampler2DRect sampler, vec2 P)");
    m_API->add("textureProj (gsampler1D sampler, vec2 P [, float bias] )");
    m_API->add("textureProj (gsampler1D sampler, vec4 P [, float bias] )");
    m_API->add("textureProj (gsampler2D sampler, vec3 P [, float bias] )");
    m_API->add("textureProj (gsampler2D sampler, vec4 P [, float bias] )");
    m_API->add("textureProj (gsampler3D sampler, vec4 P [, float bias] )");
    m_API->add("textureProj (gsampler2DRect sampler, vec3 P)");
    m_API->add("textureProj (gsampler2DRect sampler, vec4 P)");
    m_API->add("textureLod (gsampler1D sampler, float P, float lod)");
    m_API->add("textureLod (gsampler2D sampler, vec2 P, float lod)");
    m_API->add("textureLod (gsampler3D sampler, vec3 P, float lod)");
    m_API->add("textureLod (gsamplerCube sampler, vec3 P, float lod)");
    m_API->add("textureLod (gsampler1DArray sampler, vec2 P, float lod)");
    m_API->add("textureLod (gsampler2DArray sampler, vec3 P, float lod)");
    m_API->add("textureLod (gsamplerCubeArray sampler, vec4 P, float lod)");
    m_API->add("textureOffset (gsampler1D sampler, float P,int offset [, float bias] )");
    m_API->add("textureOffset (gsampler2D sampler, vec2 P,ivec2 offset [, float bias] )");
    m_API->add("textureOffset (gsampler3D sampler, vec3 P,ivec3 offset [, float bias] )");
    m_API->add("textureOffset (gsampler2DRect sampler, vec2 P,ivec2 offset )");
    m_API->add("textureOffset (gsampler1DArray sampler, vec2 P,int offset [, float bias] )");
    m_API->add("textureOffset (gsampler2DArray sampler, vec3 P,ivec2 offset [, float bias] )");
    m_API->add("texelFetch (gsampler1D sampler, int P, int lod)");
    m_API->add("texelFetch (gsampler2D sampler, ivec2 P, int lod)");
    m_API->add("texelFetch (gsampler3D sampler, ivec3 P, int lod)");
    m_API->add("texelFetch (gsampler2DRect sampler, ivec2 P)");
    m_API->add("texelFetch (gsampler1DArray sampler, ivec2 P, int lod)");
    m_API->add("texelFetch (gsampler2DArray sampler, ivec3 P, int lod)");
    m_API->add("texelFetch (gsamplerBuffer sampler, int P)");
    m_API->add("texelFetch (gsampler2DMS sampler, ivec2 P, int sample)");
    m_API->add("texelFetch (gsampler2DMSArray sampler, ivec3 P,int sample)");
    m_API->add("texelFetchOffset (gsampler1D sampler, int P, int lod,int offset)");
    m_API->add("texelFetchOffset (gsampler2D sampler, ivec2 P, int lod,ivec2 offset)");
    m_API->add("texelFetchOffset (gsampler3D sampler, ivec3 P, int lod,ivec3 offset)");
    m_API->add("texelFetchOffset (gsampler2DRect sampler, ivec2 P,ivec2 offset)");
    m_API->add("texelFetchOffset (gsampler1DArray sampler, ivec2 P, int lod,int offset)");
    m_API->add("texelFetchOffset (gsampler2DArray sampler, ivec3 P, int lod,ivec2 offset)");
    m_API->add("textureProjOffset (gsampler1D sampler, vec2 P,int offset [, float bias] )");
    m_API->add("textureProjOffset (gsampler1D sampler, vec4 P,int offset [, float bias] )");
    m_API->add("textureProjOffset (gsampler2D sampler, vec3 P,ivec2 offset [, float bias] )");
    m_API->add("textureProjOffset (gsampler2D sampler, vec4 P,ivec2 offset [, float bias] )");
    m_API->add("textureProjOffset (gsampler3D sampler, vec4 P,ivec3 offset [, float bias] )");
    m_API->add("textureProjOffset (gsampler2DRect sampler, vec3 P,ivec2 offset )");
    m_API->add("textureProjOffset (gsampler2DRect sampler, vec4 P,ivec2 offset )");
    m_API->add("textureLodOffset (gsampler1D sampler, float P,float lod, int offset)");
    m_API->add("textureLodOffset (gsampler2D sampler, vec2 P,float lod, ivec2 offset)");
    m_API->add("textureLodOffset (gsampler3D sampler, vec3 P,float lod, ivec3 offset)");
    m_API->add("textureLodOffset (gsampler1DArray sampler, vec2 P,float lod, int offset)");
    m_API->add("textureLodOffset (gsampler2DArray sampler, vec3 P,float lod, ivec2 offset)");
    m_API->add("textureProjLod (gsampler1D sampler, vec2 P, float lod)");
    m_API->add("textureProjLod (gsampler1D sampler, vec4 P, float lod)");
    m_API->add("textureProjLod (gsampler2D sampler, vec3 P, float lod)");
    m_API->add("textureProjLod (gsampler2D sampler, vec4 P, float lod)");
    m_API->add("textureProjLod (gsampler3D sampler, vec4 P, float lod)");
    m_API->add("textureProjLod (sampler1DShadow sampler, vec4 P, float lod)");
    m_API->add("textureProjLod (sampler2DShadow sampler, vec4 P, float lod)");
    m_API->add("textureProjLodOffset (gsampler1D sampler, vec2 P,float lod, int offset)");
    m_API->add("textureProjLodOffset (gsampler1D sampler, vec4 P,float lod, int offset)");
    m_API->add("textureProjLodOffset (gsampler2D sampler, vec3 P,float lod, ivec2 offset)");
    m_API->add("textureProjLodOffset (gsampler2D sampler, vec4 P,float lod, ivec2 offset)");
    m_API->add("textureProjLodOffset (gsampler3D sampler, vec4 P,float lod, ivec3 offset)");
    m_API->add("textureGrad (gsampler1D sampler, float P,float dPdx, float dPdy)");
    m_API->add("textureGrad (gsampler2D sampler, vec2 P,vec2 dPdx, vec2 dPdy)");
    m_API->add("textureGrad (gsampler3D sampler, vec3 P,vec3 dPdx, vec3 dPdy)");
    m_API->add("textureGrad (gsamplerCube sampler, vec3 P,vec3 dPdx, vec3 dPdy)");
    m_API->add("textureGrad (gsampler2DRect sampler, vec2 P,vec2 dPdx, vec2 dPdy)");
    m_API->add("textureGrad (gsampler1DArray sampler, vec2 P,float dPdx, float dPdy)");
    m_API->add("textureGrad (gsampler2DArray sampler, vec3 P,vec2 dPdx, vec2 dPdy)");
    m_API->add("textureGrad (gsamplerCubeArray sampler, vec4 P,vec3 dPdx, vec3 dPdy)");
    m_API->add("textureGradOffset (gsampler1D sampler, float P,float dPdx, float dPdy, int offset)");
    m_API->add("textureGradOffset (gsampler2D sampler, vec2 P,vec2 dPdx, vec2 dPdy, ivec2 offset)");
    m_API->add("textureGradOffset (gsampler3D sampler, vec3 P,vec3 dPdx, vec3 dPdy, ivec3 offset)");
    m_API->add("textureGradOffset (gsampler2DRect sampler, vec2 P,vec2 dPdx, vec2 dPdy, ivec2 offset)");
    m_API->add("textureGradOffset (gsampler1DArray sampler, vec2 P,float dPdx, float dPdy, int offset)");
    m_API->add("textureGradOffset (gsampler2DArray sampler, vec3 P,vec2 dPdx, vec2 dPdy, ivec2 offset)");
    m_API->add("textureProjGrad (gsampler1D sampler, vec2 P,float dPdx, float dPdy)");
    m_API->add("textureProjGrad (gsampler1D sampler, vec4 P,float dPdx, float dPdy)");
    m_API->add("textureProjGrad (gsampler2D sampler, vec3 P,vec2 dPdx, vec2 dPdy)");
    m_API->add("textureProjGrad (gsampler2D sampler, vec4 P,vec2 dPdx, vec2 dPdy)");
    m_API->add("textureProjGrad (gsampler3D sampler, vec4 P,vec3 dPdx, vec3 dPdy)");
    m_API->add("textureProjGrad (gsampler2DRect sampler, vec3 P,vec2 dPdx, vec2 dPdy)");
    m_API->add("textureProjGrad (gsampler2DRect sampler, vec4 P,vec2 dPdx, vec2 dPdy)");
    m_API->add("textureProjGradOffset (gsampler1D sampler, vec2 P,float dPdx, float dPdy, int offset)");
    m_API->add("textureProjGradOffset (gsampler1D sampler, vec4 P,float dPdx, float dPdy, int offset)");
    m_API->add("textureProjGradOffset (gsampler2D sampler, vec3 P,vec2 dPdx, vec2 dPdy, ivec2 offset)");
    m_API->add("textureProjGradOffset (gsampler2D sampler, vec4 P,vec2 dPdx, vec2 dPdy, ivec2 offset)");
    m_API->add("textureProjGradOffset (gsampler2DRect sampler, vec3 P,vec2 dPdx, vec2 dPdy, ivec2 offset)");
    m_API->add("textureProjGradOffset (gsampler2DRect sampler, vec4 P,vec2 dPdx, vec2 dPdy, ivec2 offset)");
    m_API->add("textureProjGradOffset (gsampler3D sampler, vec4 P,vec3 dPdx, vec3 dPdy, ivec3 offset)");
    m_API->add("textureGather (gsampler2D sampler, vec2 P[, int comp])");
    m_API->add("textureGather (gsampler2DArray sampler,vec3 P [, int comp])");
    m_API->add("textureGather (gsamplerCube sampler,vec3 P [, int comp])");
    m_API->add("textureGather (gsamplerCubeArray sampler,vec4 P[, int comp])");
    m_API->add("textureGather (gsampler2DRect sampler,vec2 P[, int comp])");
    m_API->add("textureGather (sampler2DShadow sampler,vec2 P, float refZ)");
    m_API->add("textureGather (sampler2DArrayShadow sampler,vec3 P, float refZ)");
    m_API->add("textureGather (samplerCubeShadow sampler,vec3 P, float refZ)");
    m_API->add("textureGather (samplerCubeArrayShadowsampler,vec4 P, float refZ)");
    m_API->add("textureGather (sampler2DRectShadow sampler,vec2 P, float refZ)");
    m_API->add("textureGatherOffset (gsampler2D sampler,vec2 P, ivec2 offset[, int comp])");
    m_API->add("textureGatherOffset (gsampler2DArray sampler,vec3 P, ivec2 offset[, int comp])");
    m_API->add("textureGatherOffset (gsampler2DRect sampler,vec2 P, ivec2 offset[, int comp])");
    m_API->add("textureGatherOffset (sampler2DShadow sampler,vec2 P, float refZ, ivec2 offset)");
    m_API->add("textureGatherOffset (sampler2DArrayShadow sampler,vec3 P, float refZ, ivec2 offset)");
    m_API->add("textureGatherOffset (sampler2DRectShadow sampler,vec2 P, float refZ, ivec2 offset)");
    m_API->add("textureGatherOffsets (gsampler2D sampler,vec2 P, ivec2 offsets[4][, int comp])");
    m_API->add("textureGatherOffsets (gsampler2DArray sampler,vec3 P, ivec2 offsets[4][, int comp])");
    m_API->add("textureGatherOffsets (gsampler2DRect sampler,vec2 P, ivec2 offsets[4][, int comp])");
    m_API->add("textureGatherOffsets (sampler2DShadow sampler,vec2 P, float refZ, ivec2offsets[4])");
    m_API->add("textureGatherOffsets (sampler2DArrayShadow sampler,vec3 P, float refZ, ivec2offsets[4])");
    m_API->add("textureGatherOffsets (sampler2DRectShadow sampler,vec2 P, float refZ, ivec2offsets[4])");
    m_API->add("texture1D (sampler1D sampler, float coord [, float bias] )");
    m_API->add("texture1DProj (sampler1D sampler, vec2 coord [, float bias] )");
    m_API->add("texture1DProj (sampler1D sampler, vec4 coord [, float bias] )");
    m_API->add("texture1DLod (sampler1D sampler, float coord, float lod)");
    m_API->add("texture1DProjLod (sampler1D sampler, vec2 coord, float lod)");
    m_API->add("texture1DProjLod (sampler1D sampler, vec4 coord, float lod)");
    m_API->add("texture2D (sampler2D sampler, vec2 coord [, float bias] )");
    m_API->add("texture2DProj (sampler2D sampler, vec3 coord [, float bias] )");
    m_API->add("texture2DProj (sampler2D sampler, vec4 coord [, float bias] )");
    m_API->add("texture2DLod (sampler2D sampler, vec2 coord, float lod)");
    m_API->add("texture2DProjLod (sampler2D sampler, vec3 coord, float lod)");
    m_API->add("texture2DProjLod (sampler2D sampler, vec4 coord, float lod)");
    m_API->add("texture3D (sampler3D sampler, vec3 coord [, float bias] )");
    m_API->add("texture3DProj (sampler3D sampler, vec4 coord [, float bias] )");
    m_API->add("texture3DLod (sampler3D sampler, vec3 coord, float lod)");
    m_API->add("texture3DProjLod (sampler3D sampler, vec4 coord, float lod)");
    m_API->add("textureCube (samplerCube sampler, vec3 coord [, float bias] )");
    m_API->add("textureCubeLod (samplerCube sampler, vec3 coord, float lod)");
    m_API->add("shadow1D (sampler1DShadow sampler, vec3 coord [, float bias] )");
    m_API->add("shadow2D (sampler2DShadow sampler, vec3 coord [, float bias] )");
    m_API->add("shadow1DProj (sampler1DShadow sampler, vec4 coord [, float bias] )");
    m_API->add("shadow2DProj (sampler2DShadow sampler, vec4 coord [, float bias] )");
    m_API->add("shadow1DLod (sampler1DShadow sampler, vec3 coord, float lod)");
    m_API->add("shadow2DLod (sampler2DShadow sampler, vec3 coord, float lod)");
    m_API->add("atomicCounterIncrement (atomic_uint c)");
    m_API->add("atomicCounterDecrement (atomic_uint c)");
    m_API->add("atomicCounter (atomic_uint c)");
    m_API->add("atomicAdd (inout uint mem, uint data)");
    m_API->add("atomicAdd (inout int mem, int data)");
    m_API->add("atomicMin (inout uint mem, uint data)");
    m_API->add("atomicMin (inout int mem, int data)");
    m_API->add("atomicMax (inout uint mem, uint data)");
    m_API->add("atomicMax (inout int mem, int data)");
    m_API->add("atomicAnd (inout uint mem, uint data)");
    m_API->add("atomicAnd (inout int mem, int data)");
    m_API->add("atomicOr (inout uint mem, uint data)");
    m_API->add("atomicOr (inout int mem, int data)");
    m_API->add("atomicXor (inout uint mem, uint data)");
    m_API->add("atomicXor (inout int mem, int data)");
    m_API->add("atomicExchange (inout uint mem, uint data)");
    m_API->add("atomicExchange (inout int mem, int data)");
    m_API->add("atomicCompSwap (inout uint mem, uint compare, uint data)");
    m_API->add("atomicCompSwap (inout int mem, int compare, int data)");
    m_API->add("imageSize (readonly writeonly gimage2D image)");
    m_API->add("imageSize (readonly writeonly gimage3D image)");
    m_API->add("imageSize (readonly writeonly gimageCube image)");
    m_API->add("imageSize (readonly writeonly gimageCubeArray image)");
    m_API->add("imageSize (readonly writeonly gimageRect image)");
    m_API->add("imageSize (readonly writeonly gimage1DArray image)");
    m_API->add("imageSize (readonly writeonly gimage2DArray image)");
    m_API->add("imageSize (readonly writeonly gimage2DMS image)");
    m_API->add("imageSize (readonly writeonly gimage2DMSArray image)");
    m_API->add("imageSamples (readonly writeonly gimage2DMS image)");
    m_API->add("imageSamples (readonly writeonly gimage2DMSArray image)");
    m_API->add("image (in IMAGE_PARAMS)");
    m_API->add("imageStore (writeonly IMAGE_PARAMS, gvec4 data)");
    m_API->add("imageAtomicAdd (IMAGE_PARAMS, uint data)");
    m_API->add("imageAtomicAdd (IMAGE_PARAMS, int data)");
    m_API->add("imageAtomicMin (IMAGE_PARAMS, uint data)");
    m_API->add("imageAtomicMin (IMAGE_PARAMS, int data)");
    m_API->add("imageAtomicMax (IMAGE_PARAMS, uint data)");
    m_API->add("imageAtomicMax (IMAGE_PARAMS, int data)");
    m_API->add("imageAtomicAnd (IMAGE_PARAMS, uint data)");
    m_API->add("imageAtomicAnd (IMAGE_PARAMS, int data)");
    m_API->add("imageAtomicOr (IMAGE_PARAMS, uint data)");
    m_API->add("imageAtomicOr (IMAGE_PARAMS, int data)");
    m_API->add("imageAtomicXor (IMAGE_PARAMS, uint data)");
    m_API->add("imageAtomicXor (IMAGE_PARAMS, int data)");
    m_API->add("imageAtomicExchange (IMAGE_PARAMS, uint data)");
    m_API->add("imageAtomicExchange (IMAGE_PARAMS, int data)");
    m_API->add("imageAtomicExchange (IMAGE_PARAMS, float data)");
    m_API->add("imageAtomicCompSwap (IMAGE_PARAMS,uint compare,uint data)");
    m_API->add("imageAtomicCompSwap (IMAGE_PARAMS,int compare,int data)");
    m_API->add("dFdx (genType p)");
    m_API->add("dFdy (genType p)");
    m_API->add("fwidthFine (genType p)");
    m_API->add("fwidthCoarse (genType p)");
    m_API->add("interpolateAtCentroid (float interpolant)");
    m_API->add("interpolateAtCentroid (vec2 interpolant)");
    m_API->add("interpolateAtCentroid (vec3 interpolant)");
    m_API->add("interpolateAtCentroid (vec4 interpolant)");
    m_API->add("interpolateAtSample (float interpolant, int sample)");
    m_API->add("interpolateAtSample (vec2 interpolant, int sample)");
    m_API->add("interpolateAtSample (vec3 interpolant, int sample)");
    m_API->add("interpolateAtSample (vec4 interpolant, int sample)");
    m_API->add("interpolateAtOffset (float interpolant, vec2 offset)");
    m_API->add("interpolateAtOffset (vec2 interpolant, vec2 offset)");
    m_API->add("interpolateAtOffset (vec3 interpolant, vec2 offset)");
    m_API->add("interpolateAtOffset (vec4 interpolant, vec2 offset)");
    m_API->add("");
    m_API->prepare();

    setAPIs(m_API);

    m_Parent->setAutoCompletionThreshold(2);
    m_Parent->setAutoCompletionFillupsEnabled(true);
    m_Parent->setAutoCompletionSource(QsciScintilla::AcsAPIs);
    m_Parent->setSelectionBackgroundColor(QColor(61,61,52));
    m_Parent->resetSelectionForegroundColor();
}

QsciLexerGLSL::~QsciLexerGLSL()
{
    delete m_API;
    delete m_FlexScanner;
}

void QsciLexerGLSL::styleText(int start, int end)
{
    m_Parent->autoCompleteFromAPIs();

    if(nullptr == editor() || start == end)
    {
        return;
    }

    std::string buf(end - start + 1, 0);

    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end, &buf[0]);
    std::istringstream iss(&buf[0]);

    int loc = 0;
    std::string tex;
    std::vector<int> tokens;
    for(int tok = m_FlexScanner->yylex(&iss);
        tok > 0;
        tok = m_FlexScanner->yylex(&iss))
    {
        tokens.push_back(tok);
        tokens.push_back(loc);
        tokens.push_back(m_FlexScanner->YYLeng());

        loc = loc + m_FlexScanner->YYLeng();

        tex = m_FlexScanner->YYText();
    }

    const size_t tokensCount = tokens.size();
    for(size_t i = 0; i < tokensCount; i += 3)
    {
        startStyling(start + tokens[i + 1]);
        setStyling(tokens[i + 2], tokens[i]);
    }
}

QColor QsciLexerGLSL::defaultColor(int style) const
{
    switch(style)
    {
    case StyleType::DEFAULT:
        return QColor(247, 247, 241);
    case StyleType::KEYWORD:
        return QColor(249, 38, 114);
    case StyleType::DATATYPE:
        return QColor(102, 216, 238);
    case StyleType::NUMBER:
        return QColor(174, 129, 255);
    case StyleType::OPERATOR:
        return QColor(249, 38, 114);
    case StyleType::STRING:
        return QColor(230, 219, 116);
    case StyleType::FUNCTION:
        return QColor(166, 226, 46);
    case StyleType::COMMENT:
        return QColor(117, 113, 94);
    case StyleType::HASHCOMMENT:
        return QColor(174, 129, 255);
    default:
        return QColor(247,247,241);
    }
}

QColor QsciLexerGLSL::defaultPaper(int style) const
{
    switch(style)
    {
    case StyleType::ILLEGAL:
        return QColor(249, 38, 114);
    default:
        return QColor(39,40,34);
    }
}

//------------------------------------------------------------------------------
QFont QsciLexerGLSL::defaultFont(int style) const
{
    int weight = 50;
    int size = 12;
    bool italic = 0;
    switch(style)
    {
    case StyleType::DEFAULT:
        weight = 50;
        size = 12;
        break;
    case StyleType::DATATYPE:
        italic = true;
        break;
    }

    return QFont("Monospace", size, weight, italic);
}

QString QsciLexerGLSL::description(int style) const
{
    switch(style)
    {
    case StyleType::NONE:
        return "NONE";
    case StyleType::DEFAULT:
        return "DEFAULT";
    case StyleType::NUMBER:
        return "NUMBER";
    case StyleType::KEYWORD:
        return "KEYWORD";
    case StyleType::FUNCTION:
        return "FUNCTION";
    case StyleType::STRING:
        return "STRING";
    case StyleType::COMMENT:
        return "COMMENT";
    case StyleType::OPERATOR:
        return "OPERATOR";
    case StyleType::WHITESPACE:
        return "WHITESPACE";
    case StyleType::DATATYPE:
        return "DATATYPE";
    default:
        return QString(style);
    }
}

const char *QsciLexerGLSL::language() const
{
    return "GLSL";
}
