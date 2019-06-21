extern crate speedreader;

use core::ptr;
use std::ffi::CStr;
use std::ffi::CString;
use std::os::raw::c_char;

/// Create a new `SpeedReader` instance.
#[no_mangle]
pub unsafe extern "C" fn speedreader_process(
    content: *const c_char,
    url: *const c_char,
    transformed: *mut *mut c_char) -> bool {
    let content = CStr::from_ptr(content).to_str().unwrap();
    let url = CStr::from_ptr(url).to_str().unwrap();

    let processed = speedreader::process(&mut content.as_bytes(), &url);

    if processed.is_empty() {
        *transformed = ptr::null_mut();
        false
    } else {
        *transformed = match CString::new(processed) {
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
