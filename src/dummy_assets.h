#pragma once

enum material_property_type
{
    MaterialProperty_Float_Shininess,
    
    MaterialProperty_Color_Ambient,
    MaterialProperty_Color_Diffuse,
    MaterialProperty_Color_Specular,
    
    MaterialProperty_Texture_Diffuse,
    MaterialProperty_Texture_Specular,
    MaterialProperty_Texture_Shininess,
    MaterialProperty_Texture_Normal
};

struct bitmap
{
    i32 Width;
    i32 Height;
    i32 Channels;
    void *Pixels;
};

struct material_property
{
    u32 Id;
    material_property_type Type;
    union
    {
        f32 Value;
        vec4 Color;
        bitmap Bitmap;
    };
};

struct mesh_material
{
    u32 PropertyCount;
    material_property *Properties;
};

struct mesh
{
    u32 Id;
    u32 MaterialIndex;

    // todo: calculate bitangent instead of storing it? (fourth weight too) <- do I even care?
    u32 VertexCount;
    vec3 *Positions;
    vec3 *Normals;
    vec3 *Tangents;
    vec3 *Bitangents;
    vec2 *TextureCoords;
    vec4 *Weights;
    i32 *JointIndices;

    u32 IndexCount;
    u32 *Indices;
};

// todo: break this?
struct model
{
    char Name[64];

    skeleton *Skeleton;
    skeleton_pose *BindPose;
    skeleton_pose *Pose;

    aabb Bounds;

    u32 MeshCount;
    mesh *Meshes;

    u32 MaterialCount;
    mesh_material *Materials;

    u32 AnimationCount;
    animation_clip *Animations;

    u32 SkinningMatrixCount;
    mat4 *SkinningMatrices;
};

struct model_asset
{
    skeleton Skeleton;
    skeleton_pose BindPose;

    u32 MeshCount;
    mesh *Meshes;

    u32 MaterialCount;
    mesh_material *Materials;

    u32 AnimationCount;
    animation_clip *Animations;
};

#pragma pack(push, 1)

struct asset_header
{

};

struct model_asset_header
{
    i32 MagicValue;
    i32 Version;
    u64 SkeletonHeaderOffset;
    u64 SkeletonPoseHeaderOffset;
    u64 MeshesHeaderOffset;
    u64 MaterialsHeaderOffset;
    u64 AnimationsHeaderOffset;
};

struct model_asset_skeleton_header
{
    u32 JointCount;
    u64 JointsOffset;
};

struct model_asset_skeleton_pose_header
{
    u64 LocalJointPosesOffset;
    u64 GlobalJointPosesOffset;
};

struct model_asset_meshes_header
{
    u32 MeshCount;
    u64 MeshesOffset;
};

struct model_asset_mesh_header
{
    u32 MaterialIndex;
    u32 VertexCount;
    u32 IndexCount;

    b32 HasPositions;
    b32 HasNormals;
    b32 HasTangents;
    b32 HasBitangets;
    b32 HasTextureCoords;
    b32 HasWeights;
    b32 HasJointIndices;

    u64 VerticesOffset;
    u64 IndicesOffset;
};

struct model_asset_materials_header
{
    u32 MaterialCount;
    u64 MaterialsOffset;
};

struct model_asset_material_header
{
    u32 PropertyCount;
    u64 PropertiesOffset;
};

struct model_asset_material_property_header
{
    material_property_type Type;
    union
    {
        f32 Value;
        vec4 Color;
        bitmap Bitmap;
    };
    u64 BitmapOffset;
};

struct model_asset_animations_header
{
    u32 AnimationCount;
    u64 AnimationsOffset;
};

struct model_asset_animation_header
{
    char Name[MAX_ANIMATION_NAME_LENGTH];
    f32 Duration;
    b32 IsLooping;
    b32 InPlace;
    u32 PoseSampleCount;
    u64 PoseSamplesOffset;
};

struct model_asset_animation_sample_header
{
    u32 JointIndex;
    u32 KeyFrameCount;
    u64 KeyFramesOffset;
};

#pragma pack(pop)
