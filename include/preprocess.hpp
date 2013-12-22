#pragma once

#ifndef NDEBUG
  #define PL0_PUBLIC		public
  #define PL0_PROTECTED		public
  #define PL0_PRIVATE		public
#else
  #define PL0_PUBLIC		public
  #define PL0_PROTECTED		protected
  #define PL0_PRIVATE		private
#endif//!NDEBUG

