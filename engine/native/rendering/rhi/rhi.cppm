module;

#include <cstdint>

export module rendering.rhi;

import rendering.rhi.vertex; // For the vertex layout

export namespace draco::rhi
{
    using BufferHandle   = uint16_t;
    using PipelineHandle = uint16_t;
    using ShaderHandle   = uint16_t;
    using ViewID         = uint16_t;

    enum class PipelineState : uint64_t {
        Default = 0,
        WriteRGB = 1 << 0,
        WriteAlpha = 1 << 1,
        MSAA = 1 << 2,
        PrimitiveTriStrip = 1 << 3,
    };

    struct RenderPacket
    {
        uint64_t sort_key;

        BufferHandle vertex_buffer;
        BufferHandle index_buffer;
        PipelineHandle pipeline;

        float model[16];
        uint32_t draw_tags;
    };

    struct PipelineDesc
    {
        ShaderHandle vs;
        ShaderHandle fs;
        PipelineState state;
    };

    inline constexpr BufferHandle InvalidBuffer = 0xFFFF;
    inline constexpr PipelineHandle InvalidPipeline = 0xFFFF;
    inline constexpr ShaderHandle InvalidShader = 0xFFFF;
    inline constexpr ViewID InvalidView = 0xFFFF;

    bool init(void* display_type, void* window_handle, uint16_t width, uint16_t height);
    void shutdown();

    void resize(uint16_t width, uint16_t height);

    // Create the shader from the given data & size
    // Note: The data should be in the format expected by the underlying graphics API
    ShaderHandle create_shader(const void* data, uint32_t size);

    // Create a pipeline from the give description
    PipelineHandle create_pipeline(const PipelineDesc&);

    // Create a vertex or index buffer from the given data & size
    BufferHandle create_vertex_buffer(const void* data, uint32_t size);
    BufferHandle create_index_buffer(const void* data, uint32_t size);

    // Helper function to set a 4x4 matrix to the identity matrix
    void identity_matrix(float* _mtx);

    // Submit a render packet to the given view for rendering
    void submit(const RenderPacket&, ViewID);

    // Begin and end the rendering of a frame
    void begin_frame();
    void end_frame();

    constexpr PipelineState operator|(PipelineState a, PipelineState b) {
        return static_cast<PipelineState>(static_cast<uint64_t>(a) | static_cast<uint64_t>(b));
    }

    constexpr bool operator&(PipelineState a, PipelineState b) {
        return static_cast<bool>(static_cast<uint64_t>(a) & static_cast<uint64_t>(b));
    }
}