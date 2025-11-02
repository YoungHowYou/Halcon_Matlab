/* Copyright 2016-2024 The MathWorks, Inc. */

#ifndef MATLAB_EXTDATA_EXCEPTION_HELPER_FUNCTIONS_HPP
#define MATLAB_EXTDATA_EXCEPTION_HELPER_FUNCTIONS_HPP

#include "publish_util.hpp"
#include "ExceptionType.hpp"
#include "FunctionType.hpp"

#include <algorithm>

MATLAB_EXTDATA_PUBLISHED_API_EXTERN_C void* get_function_ptr(int fcn);

namespace matlab {
namespace data {
namespace detail {
inline void throwIfError(int type, const std::string& customMsg = std::string()) {
    switch (ExceptionType(type)) {
    case ExceptionType::NoException:
        break;
    case ExceptionType::InvalidFieldName:
        throw InvalidFieldNameException("Field does not exist in this struct.");
    case ExceptionType::IllegalFieldName:
        throw IllegalFieldNameException("Field name is not a valid MATLAB identifier.");
    case ExceptionType::InvalidDataType:
        throw TypeMismatchException("Data type mismatch.");
    case ExceptionType::InvalidArrayType:
        throw InvalidArrayTypeException("Array type mismatch.");
    case ExceptionType::InvalidMemoryLayout:
        throw InvalidMemoryLayoutException("Memory layout mismatch.");
    case ExceptionType::InvalidDimensionsInRowMajorArray:
        throw InvalidDimensionsInRowMajorArrayException("Memory layout mismatch.");
    case ExceptionType::InvalidTypeInRowMajorArray:
        throw InvalidTypeInRowMajorArrayException("Memory layout mismatch.");
    case ExceptionType::MustSpecifyClassName:
        throw MustSpecifyClassNameException("Must specify a class name.");
    case ExceptionType::WrongNumberOfEnumsSupplied:
        throw WrongNumberOfEnumsSuppliedException("Wrong number of enums supplied.");
    case ExceptionType::OutOfMemory:
        throw matlab::OutOfMemoryException("Not enough memory available to support the request.");
    case ExceptionType::TooManyIndicesProvided:
        throw TooManyIndicesProvidedException("Too many indices provided.");
    case ExceptionType::NotEnoughIndicesProvided:
        throw NotEnoughIndicesProvidedException("Not enough indices provided.");
    case ExceptionType::StringIndexMustBeLast:
        throw StringIndexMustBeLastException("String index must be last.");
    case ExceptionType::StringIndexNotValid:
        throw StringIndexNotValidException("String index not valid for this array.");
    case ExceptionType::CanOnlyUseOneStringIndex:
        throw CanOnlyUseOneStringIndexException("Can only provide one string index.");
    case ExceptionType::InvalidArrayIndex:
        throw InvalidArrayIndexException("Array index is invalid.");
    case ExceptionType::DuplicateFieldNameInStructArray:
        throw DuplicateFieldNameInStructArrayException("Duplicate field names not allowed.");
    case ExceptionType::NonAsciiCharInRequestedAsciiOutput:
        throw NonAsciiCharInRequestedAsciiOutputException(
            "Can't create a std::string from this data.");
    case ExceptionType::CantIndexIntoEmptyArray:
        throw CantIndexIntoEmptyArrayException("Can't index into an empty array.");
    case ExceptionType::NumberOfElementsExceedsMaximum:
        throw NumberOfElementsExceedsMaximumException("Number of elements exceeds max.");
    case ExceptionType::InvalidHeterogeneousArray:
        throw ObjectArrayIncompatibleTypesException("ObjectArray not created. Elements must belong to the same class, or to classes that are part of a heterogeneous hierarchy.");
    case ExceptionType::ObjectNotAccessible:
        throw AccessingObjectNotSupportedException(customMsg);
    case ExceptionType::InvalidNumberOfElementsProvided:
        throw InvalidNumberOfElementsProvidedException(customMsg);
    case ExceptionType::ObjectNotFound:
        throw ObjectNotFoundException("Object not found.");
    case ExceptionType::WrongVectorSizeForStruct:
        throw WrongVectorSizeForStructException("Vector size is wrong for the struct.");
    case ExceptionType::PropertyExists:
        throw PropertyExistsException("The property already exists.");
    case ExceptionType::CouldNotCallConstructor:
        throw CouldNotCallConstructorException("Failed to execute class constructor.");
    case ExceptionType::HandleObjectNotFound:
        throw HandleObjectNotFoundException("Handle Object not found.");
    case ExceptionType::InvalidHeterogeneousClass:
        throw InvalidHeterogeneousClassException("ObjectArray not created. Elements must belong to the same class, or to classes that are part of a heterogeneous hierarchy.");
    case ExceptionType::InvalidHandleObjectType:
        throw InvalidHandleObjectTypeException("Invalid object type.");
    case ExceptionType::InvalidClassName:
        throw InvalidClassNameException("Requested class was not found.");
    case ExceptionType::RecursionLimitExceeded:
        throw RecursionLimitExceededException("Recursion limit exceeded.");
    case ExceptionType::PropertyNotFound:
        throw PropertyNotFoundException("Property not found.");
    case ExceptionType::InvalidPropertyValue:
        throw InvalidPropertyValueException("Invalid property value.");
    case ExceptionType::FailedToSerializeObject:
        throw FailedToSerializeObjectException("Failed to serialize object.");
    case ExceptionType::InvalidEnumerationName:
        throw InvalidEnumerationNameException("Invalid enumeration.");
    case ExceptionType::StringIsMissing:
        throw StringIsMissingException("Missing string encountered.");
    case ExceptionType::UnSuppportedOperation:
        throw UnSuppportedOperationException("Unsupported operation.");
    case ExceptionType::ObjectSerializationFailed:
        throw ObjectSerializationFailedException("Object serialization failed.");
    case ExceptionType::JavaNotSupported:
        throw JavaNotSupportedException("Java not supported.");
    case ExceptionType::FailedToLoadLibMatlabDataArray:
        throw FailedToLoadLibMatlabDataArrayException("Failed to load data.");
    case ExceptionType::FailedToResolveSymbol:
        throw FailedToResolveSymbolException("Failed to resolve symbol.");
    case ExceptionType::NonAsciiCharInInputData:
        throw NonAsciiCharInInputDataException("Input data can only contain ASCII characters.");
    case ExceptionType::InvalidDimensionsInSparseArray:
        throw InvalidDimensionsInSparseArrayException("Sparse Array can only have two dimensions.");
    case ExceptionType::FeatureNotSupported:
        throw FeatureNotSupportedException("The specified feature is not supported.");
    case ExceptionType::InvalidAssignmentForContainerArray:
        throw InvalidAssignmentForContainerArrayException("Cannot assign a container array to an element of an array created for optimization ");
    case ExceptionType::InvalidUTF8Input:
        throw InvalidUTF8InputException("Input data must contain UTF8 characters.");
    case ExceptionType::InvalidUTF16toUTF8Conversion:
        throw InvalidUTF16toUTF8ConversionException("Invalid conversion from UTF-16 input to UTF-8 encoding.");

    default:
        throw SystemErrorException("System Error.");
    }
}

template <class T>
T resolveFunctionNoExcept(FunctionType fcn) {
    void* ptr = get_function_ptr(static_cast<int>(fcn));
    return (T)ptr;
}

template <class T>
T resolveFunction(FunctionType fcn) {
    void* ptr = get_function_ptr(static_cast<int>(fcn));
    if (ptr == nullptr) {
        static const std::vector<std::pair<FunctionType, std::string>> minRelease = {
            {FunctionType::CREATE_ENUM_ARRAY, "R2018a"},
            {FunctionType::SPARSE_ARRAY_GET_INDEX_ARITHMETIC, "R2018b"},
            {FunctionType::CREATE_ARRAY_FROM_BUFFER_V2, "R2019a"},
            {FunctionType::OBJECT_SHARED_COPY, "R2020b"},
            {FunctionType::CREATE_CHAR_ARRAY_FROM_UTF8, "R2024b"},
            {FunctionType::CHAR_ARRAY_REF_GET_UTF8, "R2024b"},
            {FunctionType::CREATE_SPARSE_ARRAY_FROM_BUFFER_V2, "R2025a"},
            {FunctionType::PLACEHOLDER, "FUTURE"}};
        auto it = std::find_if(
            minRelease.rbegin(), minRelease.rend(),
            [fcn](std::pair<FunctionType, std::string> elem) { return fcn >= elem.first; });
        throw FeatureNotSupportedException(std::string("This feature requires ") +
                                           std::string(it->second.c_str()));
    }
    return (T)ptr;
}
} // namespace detail
} // namespace data
} // namespace matlab

#endif
