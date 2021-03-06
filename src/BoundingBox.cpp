#include "BoundingBox.h"
#include "ray.h"

namespace {
	inline Vec3f Min3f(const Vec3f a, const Vec3f b)
	{
		return Vec3f(MIN(a.val[0], b.val[0]), MIN(a.val[1], b.val[1]), MIN(a.val[2], b.val[2]));
	}

	inline Vec3f Max3f(const Vec3f a, const Vec3f b)
	{
		return Vec3f(MAX(a.val[0], b.val[0]), MAX(a.val[1], b.val[1]), MAX(a.val[2], b.val[2]));
	}
}

void CBoundingBox::extend(const Vec3f& p)
{
	// --- PUT YOUR CODE HERE ---

	m_minPoint = Min3f(p, m_minPoint);
	m_maxPoint = Max3f(p, m_maxPoint);
}
	
void CBoundingBox::extend(const CBoundingBox& box)
{
	// --- PUT YOUR CODE HERE ---
	extend(box.m_minPoint);
	extend(box.m_maxPoint);
}

std::pair<CBoundingBox, CBoundingBox> CBoundingBox::split(int dim, float val) const
{
	// --- PUT YOUR CODE HERE ---
	auto res = std::make_pair(*this, *this);

	res.first.m_maxPoint[dim] = val;
	res.second.m_minPoint[dim] = val;

	return res;
}

bool CBoundingBox::overlaps(const CBoundingBox& box) const
{
	// --- PUT YOUR CODE HERE ---
	//return false;

	for (int dim = 0; dim < 3; dim++) 
	{
		if (box.m_minPoint[dim] - Epsilon > m_maxPoint[dim]) return false;
		if (box.m_maxPoint[dim] + Epsilon < m_minPoint[dim]) return false;
	}

	return true;

}
	
void CBoundingBox::clip(const Ray& ray, double& t0, double& t1) const
{
	// --- PUT YOUR CODE HERE ---

    float d, den;
    if (ray.dir.val[0] != 0) 
    {
        den = 1.0f / ray.dir.val[0];

        if (ray.dir.val[0] > 0) 
        {
            if ((d = (m_minPoint.val[0] - ray.org.val[0]) * den) > t0) 
                t0 = d;
            if ((d = (m_maxPoint.val[0] - ray.org.val[0]) * den) < t1) 
                t1 = d;
        }
        else {
            if ((d = (m_maxPoint.val[0] - ray.org.val[0]) * den) > t0) 
                t0 = d;
            if ((d = (m_minPoint.val[0] - ray.org.val[0]) * den) < t1) 
                t1 = d;
        }
        if (t0 > t1) 
            return;
    }

    if (ray.dir.val[1] != 0) 
    {
        den = 1.0f / ray.dir.val[1];

        if (ray.dir.val[1] > 0) 
        {
            if ((d = (m_minPoint.val[1] - ray.org.val[1]) * den) > t0) 
                t0 = d;
            if ((d = (m_maxPoint.val[1] - ray.org.val[1]) * den) < t1) 
                t1 = d;
        }
        else 
        {
            if ((d = (m_maxPoint.val[1] - ray.org.val[1]) * den) > t0) 
                t0 = d;
            if ((d = (m_minPoint.val[1] - ray.org.val[1]) * den) < t1) 
                t1 = d;
        }
        if (t0 > t1) 
            return;
    }

    if (ray.dir.val[2] != 0) 
    {
        den = 1.0f / ray.dir.val[2];

        if (ray.dir.val[2] > 0) 
        {
            if ((d = (m_minPoint.val[2] - ray.org.val[2]) * den) > t0) 
                t0 = d;
            if ((d = (m_maxPoint.val[2] - ray.org.val[2]) * den) < t1) 
                t1 = d;
        }
        else 
        {
            if ((d = (m_maxPoint.val[2] - ray.org.val[2]) * den) > t0) 
                t0 = d;
            if ((d = (m_minPoint.val[2] - ray.org.val[2]) * den) < t1) 
                t1 = d;
        }
    }
}
	
