/* Copyright 2016-2024 The MathWorks, Inc. */

#ifndef MATLAB_EXCEPTION_TYPE_HPP_
#define MATLAB_EXCEPTION_TYPE_HPP_


namespace matlab { namespace data {
enum class ExceptionType : int {
    NoException = 0,
    InvalidArrayIndex,
    StringIndexMustBeLast,
    StringIndexNotValid,
    CantAssignArrayToThisArray,
    NotEnoughIndicesProvided,
    TooManyIndicesProvided,
    CanOnlyUseOneStringIndex,
    InvalidDataType,
    InvalidArrayType,
    InvalidFieldName,
    FailedToLoadLibMatlabDataArray,
    FailedToResolveSymbol,
    MustSpecifyClassName,
    WrongNumberOfEnumsSupplied,
    NonAsciiCharInInputData,
    NonAsciiCharInRequestedAsciiOutput,
    InvalidDimensionsInSparseArray,
    DuplicateFieldNameInStructArray,
    OutOfMemory,
    SystemError,
    CantIndexIntoEmptyArray,
    FeatureNotSupported,
    InvalidMemoryLayout,
    InvalidDimensionsInRowMajorArray,
    InvalidTypeInRowMajorArray,
    NumberOfElementsExceedsMaximum,
    InvalidHeterogeneousArray,
    ObjectNotAccessible,
    InvalidNumberOfElementsProvided,
    ObjectNotFound,
    WrongVectorSizeForStruct,
    PropertyExists,
    CouldNotCallConstructor,
    HandleObjectNotFound,
    InvalidHeterogeneousClass,
    InvalidHandleObjectType,
    InvalidClassName,
    RecursionLimitExceeded,
    PropertyNotFound,
    InvalidPropertyValue,
    FailedToSerializeObject,
    InvalidEnumerationName,
    StringIsMissing,
    UnSuppportedOperation,
    ObjectSerializationFailed,
    JavaNotSupported,
    IllegalFieldName,
    ZeroBufferSize,
    BufferSizeTooLarge,
    ArrayDimensionsExceedBufferSize,
    InvalidAssignmentForContainerArray,
    InvalidUTF8Input,
    InvalidUTF16toUTF8Conversion
};
}} // namespace matlab::data

#endif
