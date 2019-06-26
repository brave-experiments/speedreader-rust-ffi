extern crate speedreader;

use speedreader::speedreader::SpeedReader;

use core::ptr;
use std::ffi::CStr;
use std::ffi::CString;
use std::os::raw::c_char;

/// Create a new `SpeedReader instance`.
#[no_mangle]
pub unsafe extern "C" fn speedreader_create(url: *const c_char) -> *mut SpeedReader {
    let url = CStr::from_ptr(url).to_str().unwrap();
    let speedreader = SpeedReader::new(url);
    Box::into_raw(Box::new(speedreader))
}

/// Append more data to the document being processed
#[no_mangle]
pub unsafe extern "C" fn speedreader_pump(
    speedreader: *mut SpeedReader,
    content: *const c_char) {
    
    assert!(!speedreader.is_null());
    let speedreader = Box::leak(Box::from_raw(speedreader));

    if speedreader.document_readable() != Some(false) {
        let content = CStr::from_ptr(content).to_bytes();
        speedreader.with_chunk(content);
    }
}

/// Create a new `SpeedReader` instance.
#[no_mangle]
pub unsafe extern "C" fn speedreader_finalize(
    speedreader: *mut SpeedReader,
    transformed: *mut *mut c_char) -> bool {
    
    assert!(!speedreader.is_null());
    let speedreader = Box::leak(Box::from_raw(speedreader));
    
    let processed = speedreader.finalize();
    
    if speedreader.document_readable() == Some(false) || processed.is_none() {
        *transformed = ptr::null_mut();
        false
    } else {
        let extracted = processed.unwrap();
        *transformed = match CString::new(extracted) {
            Ok(y) => y.into_raw(),
            _ => ptr::null_mut(),
        };
        true
    }
}

/// Destroy a `*c_char` once you are done with it.
#[no_mangle]
pub unsafe extern "C" fn c_char_destroy(s: *mut c_char) {
    if !s.is_null() {
        drop(CString::from_raw(s));
    }
}
