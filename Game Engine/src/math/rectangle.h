#pragma once

#include "vec3.h"
#include "vec2.h"


namespace sge { namespace math {

	struct AABB;

	///
	/// Rectangle
	///
	/// Note that position is stored as a center point, and size is
	/// half-width and half-height extents.
	struct Rectangle {
		union {
			vec2 position;
			struct {
				float x;
				float y;
			};
		};
		union {
			math::vec2 size;
			struct {
				float width;
				float height;
			};
		};

		Rectangle();
		Rectangle(const AABB& aabb);
		Rectangle(const vec2& position, const math::vec2& size);
		Rectangle(float x, float y, float width, float height);

		bool intersects(const Rectangle& other) const;
		bool contains(const math::vec2& point) const;
		bool contains(const vec3& point) const;

		inline vec2 getMinimumBound() const { return position - size; }
		inline vec2 getMaximumBound() const { return position + size; }

		bool operator==(const Rectangle& other);
		bool operator!=(const Rectangle& other);

		bool operator<(const Rectangle& other) const;
		bool operator>(const Rectangle& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Rectangle& Rectangle);
	};

} }