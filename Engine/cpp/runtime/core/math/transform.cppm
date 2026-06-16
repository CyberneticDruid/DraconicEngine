module;

export module core.math.transform;
import core.math.types;
import core.stdtypes;

export namespace draco::math
{
    struct Transform
    {
        f32 position[3] = { 0.0f, 0.0f, 0.0f };
        f32 rotation[3] = { 0.0f, 0.0f, 0.0f }; // Euler (radians)
        f32 scale[3]    = { 1.0f, 1.0f, 1.0f };

        constexpr void set_position(f32 x, f32 y, f32 z) noexcept {
            position[0] = x;
            position[1] = y;
            position[2] = z;
        }

        constexpr void set_position(const Vector3& v) noexcept {
            position[0] = v.x;
            position[1] = v.y;
            position[2] = v.z;
        }

        [[nodiscard]] constexpr Vector3 get_position() const noexcept {
            return Vector3{position[0], position[1], position[2]};
        }

        constexpr void set_rotation(f32 x, f32 y, f32 z) noexcept
        {
            rotation[0] = x;
            rotation[1] = y;
            rotation[2] = z;
        }

        constexpr void set_rotation(const Vector3& v) noexcept
        {
            rotation[0] = v.x;
            rotation[1] = v.y;
            rotation[2] = v.z;
        }

        [[nodiscard]] constexpr Vector3 get_rotation() const noexcept {
            return Vector3{rotation[0], rotation[1], rotation[2]};
        }

        constexpr void set_scale(f32 x, f32 y, f32 z) noexcept
        {
            scale[0] = x;
            scale[1] = y;
            scale[2] = z;
        }

        constexpr void set_scale(const Vector3& v) noexcept
        {
            scale[0] = v.x;
            scale[1] = v.y;
            scale[2] = v.z;
        }

        [[nodiscard]] constexpr Vector3 get_scale() const noexcept {
            return Vector3{scale[0], scale[1], scale[2]};
        }

        // Compute column-major matrix from transform
        void to_matrix(f32 out[16]) const;
    };
}
