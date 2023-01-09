#include "PS_BufferHandler.hpp"
#include <cassert>
#include <cstring>

namespace ps {
    VkDeviceSize PS_BufferHandler::getAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment) {
        if (minOffsetAlignment > 0) {
            return (instanceSize + minOffsetAlignment - 1) & ~(minOffsetAlignment - 1);
        }
        return instanceSize;
    }

    PS_BufferHandler::PS_BufferHandler(PS_Device* device, VkDeviceSize instanceSize, uint32_t instanceCount,
        VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment) {
        psDevice = device;
        psHelper = new PS_Helper(device);
        this->instanceSize = instanceSize;
        this->instanceCount = instanceCount;
        this->usageFlags = usageFlags;
        this->memoryPropertyFlags = memoryPropertyFlags;
        alignmentSize = getAlignment(instanceSize, minOffsetAlignment);
        bufferSize = alignmentSize * instanceCount;
        psHelper->createBuffer(bufferSize, usageFlags, memoryPropertyFlags, buffer, memory);
    }

    PS_BufferHandler::~PS_BufferHandler() {
        unmap();
        vkDestroyBuffer(psDevice->device, buffer, nullptr);
        vkFreeMemory(psDevice->device, memory, nullptr);
    }

    VkResult PS_BufferHandler::map(VkDeviceSize size, VkDeviceSize offset) {
        assert(buffer && memory && "Called map on buffer before create");
        return vkMapMemory(psDevice->device, memory, offset, size, 0, &mapped);
    }

    void PS_BufferHandler::unmap() {
        if (mapped) {

            vkUnmapMemory(psDevice->device, memory);
            mapped = nullptr;
        }
    }

    void PS_BufferHandler::writeToBuffer(void* data, VkDeviceSize size, VkDeviceSize offset) {
        assert(mapped && "Cannot copy to unmapped buffer");

        if (size == VK_WHOLE_SIZE) {
            memcpy(mapped, data, bufferSize);
        }
        else {
            char* memOffset = (char*)mapped;
            memOffset += offset;
            memcpy(memOffset, data, size);
        }
    }

    VkResult PS_BufferHandler::flush(VkDeviceSize size, VkDeviceSize offset) {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = memory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkFlushMappedMemoryRanges(psDevice->device, 1, &mappedRange);
    }

    VkResult PS_BufferHandler::invalidate(VkDeviceSize size, VkDeviceSize offset) {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = memory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkInvalidateMappedMemoryRanges(psDevice->device, 1, &mappedRange);
    }

    VkDescriptorBufferInfo PS_BufferHandler::descriptorInfo(VkDeviceSize size, VkDeviceSize offset) {
        return VkDescriptorBufferInfo{ buffer, offset, size };
    }

    void PS_BufferHandler::writeToIndex(void* data, int index) {
        writeToBuffer(data, instanceSize, index * alignmentSize);
    }

    VkResult PS_BufferHandler::flushIndex(int index) {
        return flush(alignmentSize, index * alignmentSize);
    }

    VkDescriptorBufferInfo PS_BufferHandler::descriptorInfoForIndex(int index) {
        return descriptorInfo(alignmentSize, index * alignmentSize);
    }

    VkResult PS_BufferHandler::invalidateIndex(int index) {
        return invalidate(alignmentSize, index * alignmentSize);
    }

}