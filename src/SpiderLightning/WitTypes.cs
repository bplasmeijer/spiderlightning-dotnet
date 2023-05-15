﻿using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace SpiderLightning;

[StructLayout(LayoutKind.Sequential)]
internal unsafe struct WitString
{
    [MarshalAs(UnmanagedType.LPUTF8Str)]
    public string String;

    public int StringByteLength;

    public WitString(string value)
    {
        String = value;
        StringByteLength = Encoding.UTF8.GetByteCount(value);
    }
}

[StructLayout(LayoutKind.Sequential)]
internal unsafe struct WitByteArray
{
    public byte[] Data;
    public int DataLength;

    public WitByteArray(byte[] data)
    {
        Data = data;
        DataLength = data.Length;
    }
}

[StructLayout(LayoutKind.Sequential)]
internal unsafe struct WitBuffer
{
    public nint Data;
    public int DataLength;

    public string ToStringFromUTF8()
        => Marshal.PtrToStringUTF8(Data, DataLength);

    public byte[] ToArray()
        => new Span<byte>((void*)Data, DataLength).ToArray();
}

[StructLayout(LayoutKind.Sequential)]
internal struct WitResult<T> where T : struct
{
    public byte IsError;
    public T ResultOrError;

    public unsafe T Unwrap()
    {
        if (IsError != 0)
        {
            // We can't use fixed layout (unions) for generic structs, so manually reinterpret the ResultOrError field as a WitError
            var errorPtr = Unsafe.AsPointer(ref ResultOrError);
            var error = Marshal.PtrToStructure<WitError>((nint)errorPtr);
            throw new InvalidOperationException($"The operation failed with error code {error.Tag} and message '{error.ReadMessage()}'.");
        }

        return ResultOrError;
    }
}

[StructLayout(LayoutKind.Sequential)]
internal struct WitError
{
    public byte Tag;
    public nint MessageUtf8;
    public int MessageLength;

    public string ReadMessage()
        => Marshal.PtrToStringUTF8(MessageUtf8, MessageLength);
}
