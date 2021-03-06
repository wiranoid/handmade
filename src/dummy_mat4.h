#pragma once

struct mat4
{
    union
    {
        struct
        {
            vec4 Rows[4];
        };
        struct
        {
            f32 Elements[4][4];
        };
    };

    mat4(const mat4 &Value)
    {
        Rows[0] = Value.Rows[0];
        Rows[1] = Value.Rows[1];
        Rows[2] = Value.Rows[2];
        Rows[3] = Value.Rows[3];
    }

    explicit mat4() = default;

    explicit mat4(f32 Value)
    {
        Rows[0] = vec4(Value, 0.f, 0.f, 0.f);
        Rows[1] = vec4(0.f, Value, 0.f, 0.f);
        Rows[2] = vec4(0.f, 0.f, Value, 0.f);
        Rows[3] = vec4(0.f, 0.f, 0.f, Value);
    }

    explicit mat4(vec4 Row0, vec4 Row1, vec4 Row2, vec4 Row3)
    {
        Rows[0] = Row0;
        Rows[1] = Row1;
        Rows[2] = Row2;
        Rows[3] = Row3;
    }

    explicit mat4(
        f32 e00, f32 e01, f32 e02, f32 e03, 
        f32 e10, f32 e11, f32 e12, f32 e13, 
        f32 e20, f32 e21, f32 e22, f32 e23, 
        f32 e30, f32 e31, f32 e32, f32 e33
    )
    {
        Elements[0][0] = e00;
        Elements[0][1] = e01;
        Elements[0][2] = e02;
        Elements[0][3] = e03;

        Elements[1][0] = e10;
        Elements[1][1] = e11;
        Elements[1][2] = e12;
        Elements[1][3] = e13;

        Elements[2][0] = e20;
        Elements[2][1] = e21;
        Elements[2][2] = e22;
        Elements[2][3] = e23;

        Elements[3][0] = e30;
        Elements[3][1] = e31;
        Elements[3][2] = e32;
        Elements[3][3] = e33;
    }

    inline vec4 &operator [](u32 RowIndex)
    {
        vec4 &Result = Rows[RowIndex];
        return Result;
    }

    inline vec4 Column(u32 ColumnIndex)
    {
        vec4 Result = vec4(Elements[0][ColumnIndex], Elements[1][ColumnIndex], Elements[2][ColumnIndex], Elements[3][ColumnIndex]);
        return Result;
    }

    inline mat4 operator *(mat4 &M)
    {
        vec4 Row0 = Rows[0];
        vec4 Row1 = Rows[1];
        vec4 Row2 = Rows[2];
        vec4 Row3 = Rows[3];

        vec4 Column0 = M.Column(0);
        vec4 Column1 = M.Column(1);
        vec4 Column2 = M.Column(2);
        vec4 Column3 = M.Column(3);

        mat4 Result = mat4(
            Dot(Row0, Column0), Dot(Row0, Column1), Dot(Row0, Column2), Dot(Row0, Column3),
            Dot(Row1, Column0), Dot(Row1, Column1), Dot(Row1, Column2), Dot(Row1, Column3),
            Dot(Row2, Column0), Dot(Row2, Column1), Dot(Row2, Column2), Dot(Row2, Column3),
            Dot(Row3, Column0), Dot(Row3, Column1), Dot(Row3, Column2), Dot(Row3, Column3)
        );

        return Result;
    }

    inline vec4 operator *(const vec4 &Vector)
    {
        vec4 Row0 = Rows[0];
        vec4 Row1 = Rows[1];
        vec4 Row2 = Rows[2];
        vec4 Row3 = Rows[3];

        vec4 Result = vec4(Dot(Row0, Vector), Dot(Row1, Vector), Dot(Row2, Vector), Dot(Row3, Vector));

        return Result;
    }
};

inline mat4
Inverse(mat4 M)
{
    vec3 a = M.Column(0).xyz;
    vec3 b = M.Column(1).xyz;
    vec3 c = M.Column(2).xyz;
    vec3 d = M.Column(3).xyz;

    f32 x = M[3][0];
    f32 y = M[3][1];
    f32 z = M[3][2];
    f32 w = M[3][3];

    vec3 s = Cross(a, b);
    vec3 t = Cross(c, d);
    vec3 u = a * y - b * x;
    vec3 v = c * w - d * z;

    f32 Determinant = Dot(s, v) + Dot(t, u);

    if (Abs(Determinant) < EPSILON)
    {
        Assert(!"Inverse matrix doesn't exist");
    }

    f32 InverseDeterminant = 1.f / Determinant;

    s *= InverseDeterminant;
    t *= InverseDeterminant;
    u *= InverseDeterminant;
    v *= InverseDeterminant;

    vec3 r0 = Cross(b, v) + t * y;
    vec3 r1 = Cross(v, a) - t * x;
    vec3 r2 = Cross(d, u) + s * w;
    vec3 r3 = Cross(u, c) - s * z;

    mat4 Result = mat4(
        vec4(r0, -Dot(b, t)),
        vec4(r1, Dot(a, t)),
        vec4(r2, -Dot(d, s)),
        vec4(r3, Dot(c, s))
    );

    return Result;
}

inline mat4
Transpose(mat4 M)
{
    mat4 Result = mat4(
        M.Column(0),
        M.Column(1),
        M.Column(2),
        M.Column(3)
    );

    return Result;
}
